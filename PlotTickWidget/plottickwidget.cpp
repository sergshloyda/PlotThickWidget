
#include "plottickwidget.h"
#include <QPainter.h>
#include <QPaintEvent>
#include "qapplication.h"
#include <QRect>
#include "devicedata.h"
#include "devicesettings.h"
#include "qdebug.h"
#include "DataStructCreator.h"
#include "ThickElement.h"
#include <algorithm>
#include "DataSerializer.h"
#include "qdir.h"
#include "renderwidget.h"
#include "plotrowwidget.h"
#include <QSettings>
#include "qlayoutitem.h"
PlotTickWidget::PlotTickWidget(QWidget *parent)
	: QWidget(parent),
	sub_thick(0.0),
	us_time(),
	OscProperties(),
	_setup_mode(true),
	_main_window_mode(SetupMode),
	_conn_stat_ind(_main_window_mode==SetupMode),
	tube_mode(ON),
	ParamDirName(),
	LibraryDirName(),
	ResultDirName(),
	local_object(),
	old_nparam(1),
	dial_ld_save(nullptr),
	result_file_param_loaded(false),
	_dial_par(nullptr)
	/*OscPlotter( &OscProperties, &ed_enabled, &sub_thick, &us_time,this)*/
{
	qRegisterMetaTypeStreamOperators< QList<int> >("QList<int>");//для сохранения размеров сплиттера в настройках
	_deviceSettings = new DeviceSettings(this);
	_dev_cmd = new DeviceCmdObject(_deviceSettings,this);
	qApp->setProperty("DeviceSettings", QVariant::fromValue<DeviceSettings*>(_deviceSettings));
	qApp->setProperty("OscillogramProperties",QVariant::fromValue<OscillogramProperties*>(&OscProperties));
	_deviceSettings->loadInitialSettings();
	ui.setupUi(this);

	resize(1600,500);
	timer=new QTimer(this);
	//connect(timer, SIGNAL(timeout()), this, SLOT(received_data()));
	redraw_timer=new QTimer(this);
	//connect(redraw_timer, SIGNAL(timeout()), this, SLOT(redraw()));
	//connect(this,SIGNAL(collect_osc(const QByteArray&)),ui.osc_view,SLOT(collect_osc(const QByteArray&)));



	/*setupGridLayout=[=](QWidget* parentWidget) размещает виджеты дефектов по каналам*/
#if 1
	auto setupGridLayout=[=](QWidget* parentWidget)
	{
		_gridLayout = new QGridLayout(parentWidget);
		_gridLayout->setSpacing(0);

		_coord_label = new ChanLabel(parentWidget);

		QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Preferred);
		sizePolicy1.setHorizontalStretch(0);
		sizePolicy1.setVerticalStretch(0);
		sizePolicy1.setHeightForWidth(_coord_label->sizePolicy().hasHeightForWidth());
		_coord_label->setSizePolicy(sizePolicy1);
		_coord_label->setFrameShape(QFrame::Box);
		_coord_label->setText("");

		_gridLayout->addWidget(_coord_label, 0, 0, 1, 1);

		_coord_widget=new PlotWidget(parentWidget,new DrawCoordRow(_deviceSettings));
		_coord_widget->setFixedHeight(25);


		_gridLayout->addWidget(_coord_widget, 0, 1, 1, 1);

		_mnemo_label = new ChanLabel(parentWidget);
		sizePolicy1.setHeightForWidth(_mnemo_label->sizePolicy().hasHeightForWidth());
		_mnemo_label->setSizePolicy(sizePolicy1);
		_mnemo_label->setFrameShape(QFrame::Box);
		_mnemo_label->setText("Defects");
		_gridLayout->addWidget(_mnemo_label, 1, 0, 1, 1);

		_mnemo_widget=new PlotWidget(parentWidget,new DrawMnemoRow(_deviceSettings));
		_mnemo_widget->setFixedHeight(150);

		_gridLayout->addWidget(_mnemo_widget, 1, 1, 1, 1);


		for (quint8 i=0;i<_deviceSettings->getChansCount();i++)
		{
			PlotRowWidget* add_widget=new PlotRowWidget(parentWidget,i);
			ChanLabel* addChanLabel=new ChanLabel(parentWidget);
			add_widget->setBuddy_(addChanLabel,this);
			_row_widgets.append(add_widget);
			_row_chan_labels.append(addChanLabel);
			
		}

		for(int i=0;i<_row_widgets.count();i++)
		{
			_gridLayout->addWidget(_row_chan_labels.at(i), i+2, 0, 1, 1);
			_gridLayout->addWidget(_row_widgets.at(i), i+2, 1, 1, 1);
		}

	};

#endif
#if 0
	auto setupChanWidgets=[=](QWidget* mainWidget)
	{
		_widgets_layout = new QVBoxLayout(ui.main_widget);
		_widgets_layout->setSpacing(0);
		_widgets_layout->setContentsMargins(0, 0, 0, 0);
		_coord_widget=new PlotWidget(ui.main_widget,new DrawCoordRow(_deviceSettings));
		_coord_widget->setFixedHeight(25);
		_widgets_layout->addWidget(_coord_widget);
		_mnemo_widget=new PlotWidget(ui.main_widget,new DrawMnemoRow(_deviceSettings));
		_mnemo_widget->setFixedHeight(150);
		_widgets_layout->addWidget(_mnemo_widget);

		for (quint8 i=0;i<_deviceSettings->getChansCount();i++)
		{
			DrawStrategy* draw_strategy;
			switch(_deviceSettings->getChanMode(i))
			{
			case TD_TOL:
				draw_strategy=new DrawThickRow(i,_deviceSettings);
				break;
			case TD_TOL_LAM:
				draw_strategy=new DrawThickLamRow(i,_deviceSettings);
				break;
			case TD_DEF_PROD:
			case TD_DEF_POPER:
				draw_strategy=new DrawDefectRow(i,_deviceSettings);
				break;
			}
			_row_widgets.append(new PlotRowWidget(ui.main_widget,draw_strategy));
		}

		for(auto pos=_row_widgets.begin();pos!=_row_widgets.end();++pos)
		{
			QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
			sizePolicy.setHorizontalStretch(0);
			sizePolicy.setVerticalStretch(1);
			(*pos)->setSizePolicy(sizePolicy);
			_widgets_layout->addWidget(*pos);
		}
	};

#endif
	

	/*размещает виджет осциллограммы */
	QVBoxLayout* v_l=new QVBoxLayout(ui.OscWidget);
	v_l->setMargin(0);
	_osc_widget=new OscillogramWidget(_deviceSettings,this);
	v_l->addWidget(_osc_widget);

	_osc_widget->SetPosTester(new OscillogramPlotterSetter(&sub_thick,&us_time,this));
	_osc_widget->SetCoefficients();

	loadSettings();
	connect(this, SIGNAL(exiting()), this, SLOT(ExitWithSave()));

	/*размещает виджет настроек параметров*/

	_param_edit_tool_box=new ParamEditToolBox(this,_deviceSettings);
	ui.verticalLayout_4->addWidget(_param_edit_tool_box);

	_param_edit_tool_box->init_ed_params();
	_conn_stat_ind.InitFromWidget(_param_edit_tool_box);
	_conn_stat_ind.SetConnState(ConnStatusIndicator::Connection_ON);
	//select_channel(_deviceSettings->getSelChanNum());


	load_params(true);

	//setupChanWidgets(ui.main_widget);
	setupGridLayout(ui.main_widget);

	update_osc_widget();
	_param_edit_tool_box->select_obj_par_button();
	apply_chan_selection(_deviceSettings->getSelChanNum(),false);

#if 0
	UpdateSpectrPlotter();
#endif

	_factoryContainer=new FactoryContainer(this);
	_factoryContainer->registerFactory("DefectElementFactory",CLASSMETA(DefectElementFactory));
	_factoryContainer->registerFactory("ThickElementFactory",CLASSMETA(ThickElementFactory));
	_factoryContainer->registerFactory("ThickLamElementFactory",CLASSMETA(ThickLamElementFactory));
	_factoryContainer->registerFactory("B_ScanElementFactory",CLASSMETA(B_ScanElementFactory));

	_factoryContainer->registerFactory("SumDefectInfoFactory",CLASSMETA(SumDefectInfoFactory));
	
	QDir outputDir( QCoreApplication::applicationDirPath() );
	/*QString */filePath = outputDir.absoluteFilePath( "DataFile.dat" );
	//QList<Element_Info*> elem_list;
	qApp->setProperty("ElementList",QVariant::fromValue<QList<Element_Info*>>(_elem_list));

	setup_connections();
	showMaximized();


}

PlotTickWidget::~PlotTickWidget()
{
	if(_dial_par!=nullptr)
	{
		delete _dial_par;
		_dial_par=nullptr;
	}
	saveSettings();
	//QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
	//qDeleteAll(elem_list.begin(),elem_list.end());
	//elem_list.clear();
		qDeleteAll(_elem_list.begin(),_elem_list.end());
	_elem_list.clear();
	//delete OscPlotter;

}
void PlotTickWidget::setup_connections()
{
	connect(timer, SIGNAL(timeout()), this, SLOT(received_data()));
	connect(redraw_timer, SIGNAL(timeout()), this, SLOT(redraw()));
	connect(this,SIGNAL(collect_osc(const QByteArray&)),ui.osc_view,SLOT(collect_osc(const QByteArray&)));
	connect(ui.channel_indic,SIGNAL(ChannelLClicked(quint8 )),this,SLOT(select_channel(quint8)));
	connect(ui.channel_indic,SIGNAL(ChannelDblClicked(quint8)),this,SLOT(chan_us_set_toggled(quint8)));
	connect(_osc_widget,SIGNAL(change_curr_strob()),_param_edit_tool_box,SLOT(change_curr_strob()));
	connect(_osc_widget,SIGNAL(change_strob_length()),_param_edit_tool_box,SLOT(change_strob_length()));
	connect(_osc_widget,SIGNAL(change_strob_porog()),_param_edit_tool_box,SLOT(change_strob_porog()));
	connect(_osc_widget,SIGNAL(change_strob_begin()),_param_edit_tool_box,SLOT(change_strob_begin()));
	connect(_osc_widget,SIGNAL(change_osc_range()),_param_edit_tool_box,SLOT(change_osc_range()));
	connect(_osc_widget,SIGNAL(change_strob_porog2()),_param_edit_tool_box,SLOT(change_strob_porog2()));
	connect(_osc_widget,SIGNAL(change_strob_porog3()),_param_edit_tool_box,SLOT(change_strob_porog3()));
	connect(_osc_widget,SIGNAL(change_num_p_VRCH()),_param_edit_tool_box,SLOT(change_num_p_VRCH()));
	connect(_osc_widget,SIGNAL(change_param_p_VRCH()),_param_edit_tool_box,SLOT(change_param_p_VRCH()));

}

void PlotTickWidget::on_pushButton_clicked()
{
	if(timer->isActive())
	{
		timer->stop();
		ui.pushButton->setText("Start");
		redraw_timer->stop();
	}
	else
	{
		timer->start(60);
		redraw_timer->start(60);
		ui.pushButton->setText("Stop");
	}
}
void PlotTickWidget::on_readBtn_clicked()
{

	qDebug() << "Reading from: " << filePath ;
	DataSerializer serializer;


	auto showDeviceParams = [](  DeviceSettings* deviceSettings)
	{
		qDebug()<<deviceSettings->getChansCount();
		for(quint8  i=0;i<deviceSettings->getChansCount();i++)
		{
			const par_us_t& us=deviceSettings->getChanAmpl(static_cast<const quint8>(i));
			if ((us.on_us)&&(deviceSettings->getChanMode(i)>0))
				qDebug()<<deviceSettings->getChanModeName(i);
		}
	};
	QFile file(filePath);
	if (file.open(QIODevice::ReadOnly ))
	{
		par_device_t dev_setting;
		memset((void*)&dev_setting,0,sizeof(par_device_t));
		serializer.readFile((QIODevice*)&file,dev_setting);
		_deviceSettings->resetDeviceStruct(&dev_setting);
		showDeviceParams(_deviceSettings);
		QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
		elem_list.clear();
		serializer.readFile((QIODevice*)&file,elem_list);
		qApp->setProperty("ElementList",QVariant::fromValue<QList<Element_Info*>>(elem_list));
		_mnemo_widget->DrawPixmap(elem_list);
		for (auto pos=_row_widgets.begin();pos!=_row_widgets.end();++pos)

			(*pos)->DrawPixmap(elem_list);
	}
	else
	{
		qDebug()<<"Open file :"<<filePath<<" error!";
	}

}
//DefectElement* PlotTickWidget::createDefectElement(const amp_us_struct_t& amp_times)
//{
//	DefectElement* def_elem=new DefectElement(this);
//	for(int jj=0;jj<constants::NUM_STRB;jj++)
//	{
//		sum_strob_info_t strob_info;
//		strob_info.strob_data=amp_times.ampl[jj];
//		strob_info.flaw_size=3;
//		def_elem->strobs.push_back(strob_info);
//	}
//	return def_elem;
//}
void PlotTickWidget::on_writeBtn_clicked()
{

	qDebug() << "Writing to: " << filePath ;

	// write the file data

	QFile file(filePath);
	if (file.open(QIODevice::WriteOnly ))
	{
		DataSerializer serializer;
		QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
		serializer.writeFile((QIODevice*)&file,_deviceSettings->getDeviceStruct());
		serializer.writeFile((QIODevice*)&file,elem_list);
		qDeleteAll(elem_list.begin(),elem_list.end());
		elem_list.clear();
		qApp->setProperty("ElementList",QVariant::fromValue<QList<Element_Info*>>(elem_list));
		_mnemo_widget->DrawPixmap(elem_list);
		for (auto pos=_row_widgets.begin();pos!=_row_widgets.end();++pos)

			(*pos)->DrawPixmap(elem_list);
	}
	else
	{
		qDebug()<<"Open file :"<<filePath<<" error!";
	}
}
void PlotTickWidget::received_data()
{

	const par_thick_t &curr_thick_par = _deviceSettings->getThickParams();//задается в диалоге настроек
	const float norm_val = 0.01f * curr_thick_par.thick;
	float over_thick;
	if(curr_thick_par.thick_lim_relative)
		over_thick = norm_val * (1.0f + curr_thick_par.thick_lim_rel_pos * 0.002f);	// в 2 раза больше thick_lim_rel_pos
	else
		over_thick = norm_val + curr_thick_par.thick_lim_pos * 0.02f;	// в 2 раза больше thick_lim_rel_pos



	float min_thick = over_thick;
	float max_thick = 0;


	static int temp1=0;


	QByteArray data;
	dev_data.prepareData(data,_deviceSettings);
	const char *p_res_data = data.data();

	const ampl_header_t info_header =	DataStructCreator::CreateInfoHeader(p_res_data);
	ThickElementFactory* thick_factory=_factoryContainer->factory<ThickElementFactory>("ThickElementFactory");
	DefectElementFactory *def_factory=_factoryContainer->factory<DefectElementFactory>("DefectElementFactory");
	ThickLamElementFactory* thick_lam_factory=_factoryContainer->factory<ThickLamElementFactory>("ThickLamElementFactory");
	SumDefectInfoFactory* sum_def_info_factory=_factoryContainer->factory<SumDefectInfoFactory>("SumDefectInfoFactory");
	B_ScanElementFactory* b_scan_factory=_factoryContainer->factory<B_ScanElementFactory>("B_ScanElementFactory");
	//QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
	for(int i=0;i<info_header.count;i++)
	{
		const data_elem_header_t data_header=DataStructCreator::CreateDataElementHeader(p_res_data,info_header,i);

		Element_Info* elem_info=new Element_Info(this);
		elem_info->coord=data_header.coord;
		int offset=0;
		for(quint8 ii=0;ii<_deviceSettings->getChansCount();ii++)
		{
			if(_deviceSettings->getChanMode(ii)==TD_B_SCAN)
			{
				b_scan_us_struct_t b_scan_struct;
				DataStructCreator::FillB_ScanStruct(p_res_data,info_header,i,offset,&b_scan_struct);
			
				B_ScanElement* b_scan_element=static_cast<B_ScanElement*>(b_scan_factory->create(b_scan_struct));
				elem_info->chan_info_array.append(b_scan_element);

				offset+=sizeof(b_scan_us_struct_t);
			}
			else
			{
			amp_us_struct_t amp_times;
			
			DataStructCreator::FillAmplTimesArray(p_res_data,info_header,i,offset,amp_times);

			if((_deviceSettings->getChanMode(ii)==TD_DEF_PROD)||(_deviceSettings->getChanMode(ii)==TD_DEF_POPER))
			{
				amp_times.ampl[0].ampl = temp1 + i + 20;	
				amp_times.ampl[1].ampl = -temp1 + i;//так как беззнаковое - будет(256+(-temp1 + i))
				amp_times.ampl[2].ampl = temp1;
				amp_times.ampl[3].ampl = temp1 + i + 40;

				DefectElement* def_elem=static_cast<DefectElement*>(def_factory->create(amp_times,ii,_deviceSettings));

				elem_info->chan_info_array.append(def_elem);

			}
			else if(_deviceSettings->getChanMode(ii)==TD_TOL)
			{
				amp_times.ampl[0].ampl=temp1+60;
				amp_times.ampl[2].ampl=temp1;
				ThickElement* thick_elem=static_cast<ThickElement*>(thick_factory->create(amp_times,ii,_deviceSettings));

				thick_elem->thick.min_thick=(temp1  % 30 + 70) * 0.1f;
				thick_elem->thick.max_thick = thick_elem->thick.min_thick + (temp1 % 10) * 0.1f;


				elem_info->chan_info_array.append(thick_elem);
			}
			else if(_deviceSettings->getChanMode(ii)==TD_TOL_LAM)
			{

				amp_times.ampl[0].ampl=temp1 + i + 20;	
				amp_times.ampl[1].ampl = -temp1 + i;//так как беззнаковое - будет(256+(-temp1 + i))
				amp_times.ampl[2].ampl = temp1;
				amp_times.ampl[3].ampl = temp1 + i + 40;
				ThickLamElement* thick_lam_elem=static_cast<ThickLamElement*>(thick_lam_factory->create(amp_times,ii,_deviceSettings));
				elem_info->chan_info_array.append(thick_lam_elem);
			}

			offset+=sizeof(amp_us_struct_t);
		}
		}



		elem_info->sum_defect=sum_def_info_factory->create(elem_info->chan_info_array,_deviceSettings);
		elem_info->filled=true;

		_elem_list.append(elem_info);


	}

	temp1++;
	QRect main_widget_content_rect=contentsRect();
	int content_width=main_widget_content_rect.width();
	int qty_elems=content_width/3.0+1;
	if(_elem_list.count()>qty_elems)
	{
		delete _elem_list[0];
		_elem_list.removeAt(0);




	}

	//qApp->setProperty("ElementList",QVariant::fromValue<QList<Element_Info*>>(elem_list));

	QByteArray osc_array;
	quint8 osc_data[512];
	for (int i=0;i<512;i++)
	{
		osc_data[i]=qrand()%100;
	}
	/*
	auto serialize_into_QByteArray=[](quint8* arrSource,int size)->QByteArray
	*/
#if 1
	auto serialize_into_QByteArray=[](quint8* arrSource,int size)->QByteArray
	{
		QByteArray byteArray;

		QDataStream stream(&byteArray, QIODevice::WriteOnly);
		stream.setVersion(QDataStream::Qt_4_5);

		stream<<size;
		for(int i=0;i<size;i++)
			stream<<arrSource[i];

		return byteArray;

	};
#endif
	emit collect_osc(serialize_into_QByteArray(osc_data,512));



}
void PlotTickWidget::select_channel(quint8 num_chan)
{

	apply_chan_selection(num_chan,false);
	_deviceSettings->setCurrentNumChan(num_chan);
#if 0
	QObject* obj_osc_view=findChild<QObject*>("osc_view");
	if(obj_osc_view->metaObject()->indexOfProperty("NumChan")>0)
		obj_osc_view->setProperty("NumChan",numChan);
#endif	

	_param_edit_tool_box->apply_new_settings();
	_deviceSettings->setDeviceChangedParams(CHNG_CHAN);
	update_osc_widget();
}

void PlotTickWidget::redraw()
{
	//QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
	_coord_widget->DrawPixmap(_elem_list);
	_mnemo_widget->DrawPixmap(_elem_list);


	for (auto pos=_row_widgets.begin();pos!=_row_widgets.end();++pos)

		(*pos)->DrawPixmap(_elem_list);
}
void PlotTickWidget::on_add_vrch_point_clicked()
{
	_deviceSettings->getAmplifierPtr(_deviceSettings->getSelChanTactNum(),_deviceSettings->getSelChanAmplNum())->vrch.num_p++;
	DeviceSettings::CheckAndCorrectAllVRChTime(_deviceSettings,false);
	update_osc_widget();

}
bool PlotTickWidget::get_ed_enabled()const
{
	return _dev_cmd->en_set_device_params;
}
void PlotTickWidget::set_ed_enabled(const bool ed_enabled)
{
	_dev_cmd->en_set_device_params=ed_enabled;
}
void PlotTickWidget::dev_param_edit()
{
	if(_dial_par!=nullptr)
		_dial_par->enable_params(get_ed_enabled());
#if 0
	dial_par.EnableParams(dev_obj.en_set_device_params);

	if(dial_control_par != nullptr)
		dial_control_par->EnableParams(dev_obj.en_set_device_params);

	if(!dev_obj.en_set_device_params)
	{
		dev_obj.en_set_device_params = true;
		check_param_saving();
	}
#endif
}
void PlotTickWidget::show_gens_info(const QString& txt_info)
{
	ui.label_gens->setStyleSheet("background-color: rgb(250, 250, 250); color: rgb(250, 0, 0)");
	ui.label_gens->setText(txt_info);
}
void PlotTickWidget::show_ampl_info(const QString& txt_info)
{
	ui.label_uss->setStyleSheet("background-color: rgb(250, 250, 250); color: rgb(0, 140, 0)");
	ui.label_uss->setText(txt_info);
}
void PlotTickWidget::update_osc_widget()
{
	_osc_widget->UpdatePlotter();
}
void PlotTickWidget::update_chan_rows()
{
	QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
	for (auto pos=_row_widgets.begin();pos!=_row_widgets.end();++pos)
	{

		//qDebug()<<(*pos)->width();
		(*pos)->DrawPixmap(elem_list);
	}
}
void PlotTickWidget::reset_buffers()
{
	/*clear data buffer; update chan rows*/
}

//****************************************************slot*************************************************************
void PlotTickWidget::NoConnection()
{
}
//*****************************************************slot*************************************************************
void PlotTickWidget::slot_unsuccesfull()
{
}
//*****************************************************slot*************************************************************
void PlotTickWidget::slot_succesfull()
{
}
//*****************************************************slot*************************************************************
void PlotTickWidget::WrongDeviceMode()
{
}
//*****************************************************slot*************************************************************
void PlotTickWidget::EndInitConnection()
{

}
//*****************************************************slot*************************************************************
void PlotTickWidget::draw_osc()
{
}
//*****************************************************slot*************************************************************
void PlotTickWidget::draw_spectr()
{
}
//*****************************************************slot*************************************************************
void PlotTickWidget::collect_amps(QByteArray data)
{
}
//*********************************************Menu slot*************************************************************
void PlotTickWidget::StartStopAction()
{
}

void PlotTickWidget::SwitchToSetupMode()
{
}
void PlotTickWidget::SwitchToViewMode()
{
}
void PlotTickWidget::butt_save_par()
{
	if(dial_ld_save != nullptr)
		return;

	dial_ld_save = new DialLoadSavePar(this);
	dial_ld_save->set_butt_text(tr("\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214"));
	dial_ld_save->set_path(ParamDirName);
	dial_ld_save->set_num_par(_deviceSettings->getDeviceSettingsNum());
	dial_ld_save->set_ip(_dev_cmd->getIPAddress());
	///dial_ld_save->SetSaveMode(false, setup_mode);
	dial_ld_save->CollectParamFiles();
	dial_ld_save->show();
	dial_ld_save->setSelectedPar();

	if (dial_ld_save->exec() == QDialog::Accepted) 
	{
		ParamDirName=dial_ld_save->get_path();
		int new_param_num=dial_ld_save->get_num_par();


		_deviceSettings->setDeviceSettingsNum(new_param_num);

		saveSettings();
		save_params();

		apply_main_window_title(SetupMode);

		if(get_ed_enabled())
		{
			set_ed_enabled(false);
			_param_edit_tool_box->update_param_edit();

		}

		old_nparam = _deviceSettings->getDeviceSettingsNum();
	}

	delete dial_ld_save;
	dial_ld_save = nullptr;
}
void PlotTickWidget::butt_load_par()
{
	if(dial_ld_save != nullptr)
		return;

	dial_ld_save= new DialLoadSavePar(this);
	dial_ld_save->set_butt_text(tr("\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214"));//Загрузить
	dial_ld_save->set_path(ParamDirName);




	dial_ld_save->set_num_par(_deviceSettings->getDeviceSettingsNum());

	dial_ld_save->set_ip(_dev_cmd->ip_addr);
	///dial_ld_save->SetSaveMode(false, setup_mode);
	dial_ld_save->CollectParamFiles();
	dial_ld_save->show();
	dial_ld_save->setSelectedPar();


	if (dial_ld_save->exec() == QDialog::Accepted) 
	{
		ParamDirName=dial_ld_save->get_path();
		int new_param_num=dial_ld_save->get_num_par();

		old_nparam = _deviceSettings->getDeviceSettingsNum();
		/*dev_obj.curr_par_device.view_par.curr_nparam = new_param_num;*/
		_deviceSettings->setDeviceSettingsNum(new_param_num);
		saveSettings();

		load_params(false);
#if 0
		if(!setup_mode && ((new_set_adder.stage <= NewSetAdder::ViewShiftStage) || (new_set_adder.stage == NewSetAdder::ShiftSetStage)) )	// синхронизация параметров
			_local_settings = _loaded_settings;
#endif

	}

	delete dial_ld_save;
	dial_ld_save = nullptr;
}
void PlotTickWidget::save_par_in_dev()
{
}
void PlotTickWidget::load_par_from_dev()
{
}
void PlotTickWidget::regenerate_auto_par_set()
{
}
void PlotTickWidget::change_directories()
{
}
void PlotTickWidget::setup_params()
{
	if(_dial_par==nullptr)
		_dial_par=new DialPar(this);
	_dial_par->set_conn_settings(_dev_cmd->getIPAddress());
	//quint8 num_chans=_deviceSettings->getChansCount();
	std::vector<quint8> inputs(NUM_CHANS);
	_deviceSettings->get_inputs_from_uss(inputs);
	_dial_par->set_chans(_deviceSettings->getIzmPar(),_deviceSettings->getChanList(),inputs);
	int old_zond_freq=_deviceSettings->calculate_zond_freq();
	_dial_par->set_zond_freq(old_zond_freq);
	_dial_par->set_filtr_par(_deviceSettings->getFiltrPar());
	const par_contr_t& contr_par=_deviceSettings->getContrPar();
	_dial_par->set_control_step(contr_par.control_step);
	_dial_par->set_axis_modes(_deviceSettings);
	_dial_par->set_layer_flags(_deviceSettings->getChanList().used_layers);


	par_manual_speed_t* p_mspeed = _deviceSettings->getManualSpeedPtr();	
	if(p_mspeed->update_interval == 0)
	{
		p_mspeed->update_interval = DEF_UPDATE_INTERVAL;
		p_mspeed->time_interval = DEF_TIME_INTERVAL;
		p_mspeed->normal_speed = DEF_NORMAL_SPEED;
	}
	_dial_par->set_manual_speed(*(p_mspeed));
	_dial_par->set_coef_coord(_deviceSettings->getContrPar().coef_coord);

	_dial_par->set_string_par(_deviceSettings->getViewPar().strings);
	_dial_par->set_vdp_param(_deviceSettings->getContrPar().vdp);
	_dial_par->enable_params(get_ed_enabled());
	_dial_par->show();
	if (_dial_par->exec() == QDialog::Accepted) 
	{
		QString temp_ip_addr=_dial_par->get_conn_settings();//dial_par.get_conn_settings(&temp_ip_addr);

		par_filtr_t filtr_par;
		_dial_par->get_filtr_par(filtr_par);
		_deviceSettings->setFiltrPar(filtr_par);//dial_par.get_filtr_par(&dev_obj.curr_par_device.contr_par.trk_par.filtr_par);

		par_manual_speed_t manual_speed;
		_dial_par->get_manual_speed(manual_speed);
		_deviceSettings->setManualSpeedPar(manual_speed);//dial_par.get_manual_speed(&mspeed);

		_deviceSettings->setCoeffCoord(_dial_par->get_coef_coord());//dial_par.get_coef_coord(&dev_obj.curr_par_device.contr_par.coef_coord);

		par_info_strings_t str_par;
		_dial_par->get_string_par(&str_par);
		_deviceSettings->setStringPar(&str_par);//dial_par.get_string_par(&dev_obj.curr_par_device.view_par.strings);


		par_vdp_t vdp_par;
		_dial_par->get_vdp_param(&vdp_par);
		_deviceSettings->setVDPPar(vdp_par);//dial_par.get_vdp_param(&dev_obj.curr_par_device.contr_par.vdp);

		_deviceSettings->setTactsQty(_dial_par->get_num_tacts());//trk_par.izm_par.num_tacts = dial_par.GetNumTacts();
		_param_edit_tool_box->set_tact_limits();//par_ed.set_tact_limits();

		/*int new_zond_freq;
		if(dial_par.get_zond_freq(&new_zond_freq))
		{
		quint16 Thp_Tt = calculate_Thp_Tt(new_zond_freq);


		if(Thp_Tt > (2*DEF_LEN_HIPOW+T_DEL_IZL+MIN_LEN_TACT))
		{
		for(quint8 i = 0; i < NUM_TACTS; i++)
		{
		trk_par.takts[i].len_tact = Thp_Tt - (2*DEF_LEN_HIPOW + T_DEL_IZL);
		trk_par.takts[i].len_hipow = DEF_LEN_HIPOW;
		}
		}
		}*/
		int new_zond_freq=_dial_par->get_zond_freq();
		if(new_zond_freq>0)
		{
			_deviceSettings->setTactsSettingParameters(new_zond_freq);
		}


		_deviceSettings->setChansQty(_dial_par->get_num_chans());//	cn_list.chan_count = dial_par.GetNumChans();

		/*	dial_par.get_chans(cn_list.cn_info, input_us);
		set_inputs_to_uss(input_us);*/
		std::vector<std::tuple<quint8,quint8,quint8>> chan_info;
		std::vector<quint8> inputs;
		_dial_par->get_chans(chan_info,inputs);


		for(int i=0;i<NUM_CHANS;i++)
		{
			std::tuple<quint8,quint8,quint8> chan=chan_info[i];
			quint8 tact=std::get<0>(chan);
			quint8 nus=std::get<1>(chan);
			quint8 rej=std::get<2>(chan);
			_deviceSettings->setChanInfoNumTact(i,tact);
			_deviceSettings->setChanInfoAmplNum(i,nus);
			_deviceSettings->setChanInfoMode(i,rej);
		}
		for(quint8 i = 0; i < _deviceSettings->getChansCount(); i++)
		{
			par_us_t* p_curr_us=_deviceSettings->getChanAmplifierPtr(i);
			_deviceSettings->setAmplInputNum(p_curr_us,inputs[i]);
		}

		/*
		for(quint8 i = 0; i < NUM_TACTS; i++)	// сбрасывание режимов всех училителей, дабы не было лишней толщинометрии в остальных каналах
		{
		for(quint8 j = 0; j < NUM_USS; j++)
		trk_par.takts[i].uss[j].rej = TD_DEF;
		}

		*/
		for(quint8 i = 0; i < NUM_TACTS; i++)	// сбрасывание режимов всех усилителей, дабы не было лишней толщинометрии в остальных каналах
		{
			for(quint8 j = 0; j < NUM_USS; j++)
				_deviceSettings->setAmplMode(i,j,TD_DEF); 
		}



		/*
		quint8 states[NUM_TACTS][NUM_USS] = {0};

		for(quint8 i = 0; i < cn_list.chan_count; i++)		// применение типа усилителей
		{
		cn_info_t *cn_info = cn_list.cn_info + i;
		par_us_t &curr_us = trk_par.takts[cn_info->ntact].uss[cn_info->nus];
		curr_us.rej = cn_info->rej & TD_MASK;

		states[cn_info->ntact][cn_info->nus] = 1;

		if(curr_us.rej != TD_DEF)
		{
		for(quint8 j = 0 ; j < NUM_STRBS; j++)
		cn_info->strb_info[j].on_extra_por = OFF;
		}
		}
		*/
		quint8 states[NUM_TACTS][NUM_USS] = {0};
		for(quint8 chan = 0;  chan <_deviceSettings->getChansCount(); chan++)		// применение типа усилителей
		{
			par_us_t* p_curr_us=_deviceSettings->getChanAmplifierPtr(chan);
			const cn_info_t& cn_info=_deviceSettings->getChanInfo(chan);

			p_curr_us->rej=cn_info.rej&TD_MASK;

			states[cn_info.ntact][cn_info.nus] = 1;

			if(p_curr_us->rej != TD_DEF)
			{
				for(quint8 strob = 0 ; strob < NUM_STRBS; strob++)
				{
					par_strb_info_t* p_strb_info=_deviceSettings->getStrobInfoPtr(chan,strob);
					p_strb_info->on_extra_por=OFF;
				}

			}
		}

		/*
		for(quint8 i = 0; i < NUM_TACTS; i++)
		{
		for(quint8 j = 0; j < NUM_USS; j++)
		{
		if(trk_par.takts[i].uss[j].on_us && !states[i][j])		// выключение неиспользуемых усилителей
		trk_par.takts[i].uss[j].on_us = OFF;
		}
		}*/
		for(quint8 tact = 0; tact < NUM_TACTS; tact++)
		{
			for(quint8 us = 0; us < NUM_USS; us++)
			{
				par_us_t* p_curr_us=_deviceSettings->getAmplifierPtr(tact,us);
				if(p_curr_us->on_us && !states[tact][us])		// выключение неиспользуемых усилителей
					p_curr_us->on_us = OFF;
			}
		}

		_deviceSettings->setUsedLayers(_dial_par->get_layer_flags());//	cn_list.used_layers = dial_par.get_layer_flags();


		/*
		const cn_info_t &curr_cn_info = cn_list.cn_info[dev_obj.curr_par_device.view_par.nchan];
		par_osc_t &osc_par = dev_obj.curr_par_device.view_par.osc_par;


		osc_par.nus = curr_cn_info.nus;
		osc_par.ntact = curr_cn_info.ntact;
		osc_par.ninp = trk_par.takts[curr_cn_info.ntact].uss[curr_cn_info.nus].us_input;
		*/
		const cn_info_t &curr_cn_info=_deviceSettings->getSelChanInfo();
		_deviceSettings->setOscAmplNum(curr_cn_info.nus);
		_deviceSettings->setOscTactNum(curr_cn_info.ntact);
		_deviceSettings->setOscInputNum(inputs[_deviceSettings->getSelChanNum()]);

		par_izm_t* izm_par=_deviceSettings->getIzmParPtr();
		izm_par->num_per_elem=_dial_par->get_number_per_element();//	trk_par.izm_par.num_per_elem = dial_par.GetNumPerElem();

		_deviceSettings->setControlStep(_dial_par->get_control_step());//	dial_par.get_control_step(&dev_obj.curr_par_device.contr_par.control_step);

#if 0
		ui_set.v_scan->SetMABParams(&dev_obj.curr_par_device.view_par.mab_par);
#endif

		/*
		par_ed.apply_chan();
		par_ed.apply_strob_extra_por();
		par_ed.apply_us_rej();
		par_ed.apply_strob_exrta_por_a();

		par_ed.set_tact_params();
		par_ed.apply_thick_corr_par();
		par_ed.apply_luch_par();
		par_ed.apply_scale_mode();
		*/

		_param_edit_tool_box->apply_new_settings();


#if 0
		reapply_respond_arrays();
		reset_exec_trees();
		ResetChanalRowArr(setup_mode);
		plot_setter.set_visible_chanals(cn_list.chan_count, cn_list.cn_info, &dev_obj.curr_par_device.contr_par.trk_par);

		chan_proc.UpdateLastValues();
		apply_chan_selection();

		ResetRowPlotters();


		UpdateOscPlotter();
		UpdateSpectrPlotter();
#endif
		//select_channel(_deviceSettings->getSelChanNum());
		apply_chan_selection(_deviceSettings->getSelChanNum(),false);
		update_osc_widget();
		redraw();
		if(_dial_par->modified())
		{
		qDeleteAll(_elem_list.begin(),_elem_list.end());
		_elem_list.clear();
		reset_row_widgets();
		}
		//update_chan_rows();

		/*

		//	beam_info.SetVisible(false);


		bool conn_change = (temp_ip_addr != dev_obj.ip_addr);


		bool was_inited = dev_obj.IsAttached();

		if(conn_change)
		{
		if(was_inited)
		dev_obj.StopDevice();

		dev_obj.ip_addr = temp_ip_addr;

		if(was_inited)
		dev_obj.SetupDevice();
		}
		else if(was_inited)
		{
		dev_obj.g_changed_param |= CHNG_ALL;

		OnStopAction();			// всё связанное с контроллером выключается
		}


		saveSettings();

		}
		*/
	}



}
void PlotTickWidget::show_mab_setup()
{
}
void PlotTickWidget::show_channel_setup()
{
}
void PlotTickWidget::show_algor_setup()
{
}
void PlotTickWidget::show_selection_setup()
{
}
//*****************************************************load&save settings************************************************************
void PlotTickWidget::saveSettings()
{

	QSettings settings( QCoreApplication::applicationDirPath()+"//qwin_octopuz.ini",
		QSettings::IniFormat);
	settings.setValue("mainWindowGeometry", saveGeometry());

	settings.setValue("ParamDirName", ParamDirName);
	settings.setValue("LibraryDirName", LibraryDirName);
	settings.setValue("ResultDirName", ResultDirName);


	settings.setValue("curr_nparam", _deviceSettings->getDeviceSettingsNum());

	settings.setValue("is_tube_mode", tube_mode);

	settings.setValue("ip_addr", _dev_cmd->ip_addr);
	settings.setValue("port", _dev_cmd->port);


	settings.setValue("curr_month", local_object.month);
	settings.setValue("curr_date", local_object.date);

	settings.setValue("curr_shift", local_object.shift);
	settings.setValue("curr_control_time", local_object.control_time);
	settings.setValue("curr_defectoskopist", local_object.defectoskopist);
	settings.setValue("curr_tabel_num", local_object.tabel_num);

	if(local_object.consignment != "SOP")
		settings.setValue("curr_consignment", local_object.consignment);
	else
		settings.setValue("curr_consignment", "");
	settings.setValue("curr_sertificate", local_object.sertificate);



	QVariant variant;
	variant.setValue<QList<int>>(ui.splitter->sizes());
	settings.setValue("Splitter_main", variant );

	//variant.setValue<QList<int>>(ui_set.splitter_osc->sizes());
	//settings.setValue("Splitter_osc", variant );


	//settings.setValue("v_scan_scroll_h", ui_set.v_scan_scroll->horizontalScrollBar()->value());
}

void PlotTickWidget::loadSettings()
{
	QSettings settings( QCoreApplication::applicationDirPath()+"//qwin_octopuz.ini",
		QSettings::IniFormat);
	restoreGeometry(settings.value("mainWindowGeometry").toByteArray());


	ParamDirName = settings.value("ParamDirName",tr("D:/\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270")).toString();
	/*D:/Настройки*/
	LibraryDirName = settings.value("LibraryDirName",tr("D:/\320\221\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270")).toString();
	/*D:/Библиотеки*/
	ResultDirName = settings.value("ResultDirName", tr("D:/\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202\321\213")).toString();
	/*D:/Результаты*/



	_deviceSettings->setDeviceSettingsNum(settings.value("curr_nparam", DEF_NUM_PARAM).toInt());

	tube_mode = settings.value("is_tube_mode", ON).toInt();


	_dev_cmd->ip_addr = settings.value("ip_addr", "192.168.18.184").toString();
	_dev_cmd->port = settings.value("port", "2000").toInt();


	local_object.month = settings.value("curr_month", local_object.month).toString();
	local_object.date = settings.value("curr_date", local_object.date).toString();

	local_object.shift = settings.value("curr_shift", local_object.shift).toString();
	local_object.control_time = settings.value("curr_control_time", local_object.control_time).toString();
	local_object.defectoskopist = settings.value("curr_defectoskopist", local_object.defectoskopist).toString();
	local_object.tabel_num = settings.value("curr_tabel_num", local_object.tabel_num).toString();

	local_object.consignment = settings.value("curr_consignment", local_object.consignment).toString();
	local_object.sertificate = settings.value("curr_sertificate", local_object.sertificate).toString();



	QList<int> default_splitter_size;
	default_splitter_size << 200 << 200;
	QVariant default_variant;
	default_variant.setValue<QList<int>>(default_splitter_size);
	QVariant load_variant=settings.value("Splitter_main",  default_variant);
	ui.splitter->setSizes(load_variant.value< QList<int> >());
	//ui.splitter->setSizes( settings.value("Splitter_main",  default_variant).value<QList<int>>() );


	//default_splitter_size << 200;
	//default_variant.setValue<QList<int>>(default_splitter_size);
	//ui_set.splitter_osc->setSizes( settings.value("Splitter_osc",  default_variant).value<QList<int>>() );

	//ui_set.v_scan_scroll->horizontalScrollBar()->setValue(settings.value("v_scan_scroll_h", 0).toInt());

}
void PlotTickWidget::closeEvent(QCloseEvent *event)
{
	bool is_edit_params;

	is_edit_params=get_ed_enabled();

	if(_dev_cmd->IsAttached())
		_dev_cmd->StopDevice();

	if(is_edit_params)
	{
		event->ignore();
		emit exiting();
	}
	else
		event->accept();

	//	QMainWindow::closeEvent(event);
}
void PlotTickWidget::ExitWithSave()
{
	if(get_ed_enabled())
	{
		check_param_saving();
	}
	QCoreApplication::exit(0);
}

void PlotTickWidget::check_param_saving()	// вероятно, не учитывается переключение режима труба/пруток при пересохранении ???
{


	if(!get_ed_enabled())		// если редактирование выключено, параметры уже были сохранены
		return;

	QMessageBox mb( tr("\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\321\203?"), 
		/*Сохранить настройку?*/
		tr("\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270, \320\262\320\276\320\267\320\274\320\276\320\266\320\275\320\276, \320\261\321\213\320\273\320\270 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\321\213. \n\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\321\203 \342\204\226 %1 ?").arg(old_nparam, 0, 10),
		/*Параметры настройки, возможно, были изменены. 
		Сохранить настройку № %1 ?*/
		QMessageBox::Question,
		QMessageBox::Yes,
		QMessageBox::No | QMessageBox::Default | QMessageBox::Escape,
		QMessageBox::NoButton  );

	mb.setButtonText(QMessageBox::Yes, tr("\320\224\320\260"));
	mb.setButtonText(QMessageBox::No, tr("\320\235\320\265\321\202"));

	int new_nparam = _deviceSettings->getDeviceSettingsNum();

	_deviceSettings->setDeviceSettingsNum( old_nparam);

	if(mb.exec() == QMessageBox::Yes)
		butt_save_par();


	//dev_obj.curr_par_device.view_par.curr_nparam = new_nparam;
	_deviceSettings->setDeviceSettingsNum(new_nparam);
	//dev_obj.en_set_device_params = false;
	set_ed_enabled(false);

	_param_edit_tool_box->update_param_edit();
#if 0
	dial_par.EnableParams(dev_obj.en_set_device_params);
	if(dial_control_par != nullptr)
		dial_control_par->EnableParams(dev_obj.en_set_device_params);
#endif

}
bool PlotTickWidget::load_params(bool startup, bool load_strings)
{

	if(!startup && get_ed_enabled())
		check_param_saving();

	quint16 num_settings=_deviceSettings->getDeviceSettingsNum();
	if(false==_deviceSettings->load_from_file_session_params(num_settings,ParamDirName))/*!load_from_file_session_params(dev_obj.curr_par_device.view_par.curr_nparam, load_strings)*/
	{
		bool result = true;

		if(!startup)
		{
			QMessageBox mb( tr("\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\277\320\276"
				" \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216"), 
				/*Настройки по умолчанию*/
				tr("\320\222\321\213 \321\205\320\276\321\202\320\270\321\202\320\265"
				" \320\267\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214"
				" \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270"
				" \320\277\320\276 \321\203\320\274\320\276\320\273\321\207\320\260\320\275\320\270\321\216?"
				" \320\242\320\265\320\272\321\203\321\211\320\270\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270"
				" \320\261\321\203\320\264\321\203\321\202 \321\201\320\261\321\200\320\276\321\210\320\265\320\275\321\213."),
				/*
				Вы хотите загрузить настройки по умолчанию? Текущие настройки будут сброшены.
				*/
				QMessageBox::Question,
				QMessageBox::Yes,
				QMessageBox::No | QMessageBox::Default | QMessageBox::Escape,
				QMessageBox::NoButton  );

			mb.setButtonText(QMessageBox::Yes, tr("\320\224\320\260"));
			mb.setButtonText(QMessageBox::No, tr("\320\235\320\265\321\202"));

			result = (mb.exec() == QMessageBox::Yes);
		}

		if(result)
		{
			quint16 old_par_num = _deviceSettings->getDeviceSettingsNum();
			_deviceSettings->loadInitialSettings();
			_deviceSettings->setDeviceSettingsNum(old_par_num);
			// установка всех параметров по умолчанию ???


			QString old_ip_addr = _dev_cmd->getIPAddress();
			loadSettings();


			const par_thick_t &thick_par = _deviceSettings->getThickParams();
			const par_object_t& object_par=_deviceSettings->getObjectPar();
			if(thick_par.thick_lim_relative)
				_loaded_settings.sizing = tr("%1 \321\205 %2 +%3% -%4%") .arg(object_par.diameter * 0.1f, 0, 'f', 1)
				.arg(thick_par.thick * 0.01f, 0, 'f', 2)
				.arg(thick_par.thick_lim_rel_pos * 0.1f, 0, 'f', 1)
				.arg(thick_par.thick_lim_rel_neg * 0.1f, 0, 'f', 1);
			else
				_loaded_settings.sizing = tr("%1 \321\205 %2 +%3 -%4") .arg(object_par.diameter * 0.1f, 0, 'f', 1)
				.arg(thick_par.thick * 0.01f, 0, 'f', 2)
				.arg(thick_par.thick_lim_pos * 0.01f, 0, 'f', 1)
				.arg(thick_par.thick_lim_neg * 0.01f, 0, 'f', 1);

			_local_settings.sizing = _loaded_settings.sizing;

			_dev_cmd->setIPAddress(old_ip_addr);
		}
		else
			return false;
	}
	else
	{
		if(load_strings)				// если строки не синхронизировались, то их не обновляем
		{
			if(_main_window_mode==SetupMode)						// в режиме настройки - синхронизация
				_local_settings = _loaded_settings;
			else									// иначе только синхронизация описания и размеров (???)
			{
				_local_settings.ParamDefinition = _loaded_settings.ParamDefinition;
				_local_settings.sizing = _loaded_settings.sizing;
			}
		}
		else
		{
			const par_thick_t &thick_par = _deviceSettings->getThickParams();
			const par_object_t& object_par=_deviceSettings->getObjectPar();

			if(thick_par.thick_lim_relative)
				_loaded_settings.sizing = tr("%1 \321\205 %2 +%3% -%4%") .arg(object_par.diameter * 0.1f, 0, 'f', 1)
				.arg(thick_par.thick * 0.01f, 0, 'f', 2)
				.arg(thick_par.thick_lim_rel_pos * 0.1f, 0, 'f', 1)
				.arg(thick_par.thick_lim_rel_neg * 0.1f, 0, 'f', 1);
			else
				_loaded_settings.sizing = tr("%1 \321\205 %2 +%3 -%4") .arg(object_par.diameter * 0.1f, 0, 'f', 1)
				.arg(thick_par.thick * 0.01f, 0, 'f', 2)
				.arg(thick_par.thick_lim_pos * 0.01f, 0, 'f', 1)
				.arg(thick_par.thick_lim_neg * 0.01f, 0, 'f', 1);

			_local_settings.sizing = _loaded_settings.sizing;
		}
	}


	old_nparam = _deviceSettings->getDeviceSettingsNum();


	// применение настроек
#if 0
	ui_set.v_scan->SetMABParams(&dev_obj.curr_par_device.view_par.mab_par);
#endif

	_param_edit_tool_box->apply_new_settings();

	//reapply_respond_arrays();//выставляются размеры элементов для массива результатов(вероятно не нужно)?
	//reset_exec_trees();//используется для алгоритма
#if 0
	ResetChanalRowArr(setup_mode);//переподключаются каналы к массиву результатов result_view , если рабочий режим или к auto_collect, если режим настройки

	const cn_list_t &cn_list = dev_obj.curr_par_device.contr_par.trk_par.cn_list;
	plot_setter.set_visible_chanals(cn_list.chan_count, cn_list.cn_info, &dev_obj.curr_par_device.contr_par.trk_par);

	chan_proc.UpdateLastValues();//заполнение из плоского массива, векторов результатов

	apply_chan_selection();


	ResetRowPlotters();



	UpdateOscPlotter();
	UpdateSpectrPlotter();
#endif
	select_channel(_deviceSettings->getSelChanNum());
	update_osc_widget();
	//	beam_info.SetVisible(false);

	apply_main_window_title(_main_window_mode);
	if(_main_window_mode==ViewMode)
	{
#if 0
		ui_view.label_curr_setting->setText(tr("\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \342\204\226%1").arg(_deviceSettings->getDeviceSettingsNum()));
		ui_view.label_setting_descr->setText(tr("\"%1\"").arg(_local_settings.ParamDefinition));

		new_set_adder.ReApplyParConsignment();
		// ??????


		ui_view.checkBox_scale_mode->setChecked(dev_obj.curr_par_device.view_par.scale_thick_to_limits);
#endif
	}

	result_file_param_loaded = false;

	_deviceSettings->setDeviceChangedParams( CHNG_ALL);

	return true;
}

bool PlotTickWidget::save_params()
{
	return _deviceSettings->save_to_file_session_params(_deviceSettings->getDeviceSettingsNum(),ParamDirName,_dev_cmd->getIPAddress());
}
void PlotTickWidget::apply_main_window_title(MainWindowMode window_mode)
{
	if(window_mode==SetupMode)
	{
		setWindowTitle(tr("study_sepia:   \320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\260 \342\204\226 %1   %2 %3  '%4'").arg(_deviceSettings->getDeviceSettingsNum(), 0, 10).arg(QString("\320\242\321\200\321\203\320\261\320\260"), _local_settings.sizing, _local_settings.ParamDefinition) );
	}
	else if(window_mode==ViewMode)
	{
		setWindowTitle(tr("q_win_sepia_view"));
	}
}
void PlotTickWidget::chan_us_set_toggled(quint8 numChan)
{

	if(_main_window_mode==ViewMode)
		return;
#if 0

	if(dev_obj.curr_par_device.view_par.nchan != chan)		// для корректной работы добавить задержку ???
	{
		dev_obj.curr_par_device.view_par.nchan = chan;

		par_ed.apply_chan();
		par_ed.apply_strob_extra_por();
		par_ed.apply_us_rej();
		par_ed.apply_strob_exrta_por_a();

		chan_changed();
	}

	slot_us_on_off();


	if(!dev_obj.en_set_device_params)
		return;

	par_osc_t &osc_par = dev_obj.curr_par_device.view_par.osc_par;
	par_trk_t &trk_par = dev_obj.curr_par_device.contr_par.trk_par;

	par_us_t &curr_us = trk_par.takts[osc_par.ntact].uss[osc_par.nus];

	curr_us.on_us = curr_us.on_us ? OFF : ON;

	par_ed.apply_us_on();
	par_ed.show_on_uss();
	par_ed.apply_channals_states();

	ui_set.v_scan->ShowGensUss(osc_par.ntact, dev_obj.curr_par_device.contr_par.trk_par.takts);


	const cn_list_t &cn_list = trk_par.cn_list;
	plot_setter.set_visible_chanals(cn_list.chan_count, cn_list.cn_info, &trk_par);
	dev_obj.g_changed_param |= CHNG_ONUS;
#endif
}

void PlotTickWidget::apply_chan_selection(const quint8 num_chan,const bool replot)
{


	for (auto pos=_row_widgets.begin();pos!=_row_widgets.end();++pos){
		if((*pos)->getNumChan()==num_chan)
			(*pos)->getBuddy_()->drawFrame=true;
		else
			(*pos)->getBuddy_()->drawFrame=false;

		(*pos)->getBuddy_()->update();
	}
#if 0
	if(replot)
	{
		for(quint8 i = 0; i < dev_obj.curr_par_device.contr_par.trk_par.cn_list.chan_count; i++)
			ChanRowArr[i]->ResetPlot();
	}
#endif
}
void PlotTickWidget::changeColors()
{
	/* здесь должен вызываться диалог настроек цветовой схемы*/
}

void PlotTickWidget::reset_row_widgets()
{
	_row_widgets.clear();
	_row_chan_labels.clear();
	for (quint8 i=0;i<_deviceSettings->getChansCount();i++)
		{
			//qDebug()<<_deviceSettings->getChanModeName(i);
			PlotRowWidget* add_widget=new PlotRowWidget(ui.main_widget,i);
			ChanLabel* addChanLabel=new ChanLabel(ui.main_widget);
			add_widget->setBuddy_(addChanLabel,this);
			_row_widgets.append(add_widget);
			_row_chan_labels.append(addChanLabel);
		}
	QLayoutItem *wItem;
while ((wItem = _gridLayout->takeAt(0)) != 0)
    delete wItem;
_gridLayout->addWidget(_coord_widget, 0, 1, 1, 1);
_gridLayout->addWidget(_mnemo_widget, 1, 1, 1, 1);
		for(int i=0;i<_row_widgets.count();i++)
		{
			_gridLayout->addWidget(_row_chan_labels.at(i), i+2, 0, 1, 1);

			//_row_chan_labels.at(i)->setText(_deviceSettings->getChanModeName(i));
			_gridLayout->addWidget(_row_widgets.at(i), i+2, 1, 1, 1);
		}
		 QTimer::singleShot(5, this, SLOT(redraw()));//задержка для того, чтобы успеть вычислить размеры виджетов после layout
}
