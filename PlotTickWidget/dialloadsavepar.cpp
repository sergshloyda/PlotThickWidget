#include "dialloadsavepar.h"
#include "params.h"
#include "dev_struct.h"
DialLoadSavePar::DialLoadSavePar(QWidget *parent):
    QDialog(parent, Qt::Window),
	DirName(),
	curr_ip(),

	save_mode(false),
	param_handler_setted(false),
    ui(),
	selectionModel(nullptr),
	selected_par(1),
	recursive_select(false)

	{
		ui.setupUi(this);
		//ui.tableView_files->setStyleSheet("QTableView::item {selection-background-color: rgb(30, 144, 255);selection-color:rgb(255,255,255);} QHeaderView::section { background-color:lightGray }");


		//table_model.setColumnCount(8);
		//
		//table_model.setHeaderData(0, Qt::Horizontal, tr("\342\204\226"));//№


		//table_model.setHeaderData(1, Qt::Horizontal, tr("\320\236\320\277\320\270\321\201\320\260\320\275\320\270\320\265"));//Описание
		//table_model.setHeaderData(2, Qt::Horizontal, tr("\320\237\321\200\320\270\320\274\320\265\320\275\320\265\320\275\320\270\320\265"));//Применение

		//table_model.setHeaderData(3, Qt::Horizontal, tr("\320\232\320\276\320\275\321\202\321\200\320\276\320\273\320\270\321\200.\321\202\320\276\320\273\321\211"));
		////Контролир.толщ

		//table_model.setHeaderData(4, Qt::Horizontal, tr("\320\234\320\265\321\205-\320\220\320\272\321\203\321\201\321\202.\320\261\320\273\320\276\320\272"));
		////Мех-Акуст.блок
		//table_model.setHeaderData(5, Qt::Horizontal, tr("\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274"));
		////Алгоритм
		//table_model.setHeaderData(6, Qt::Horizontal, tr("\320\224\320\260\321\202\320\260 \321\201\320\276\320\267\320\264\320\260\320\275\320\270\321\217"));
		////Дата создания
		//table_model.setHeaderData(7, Qt::Horizontal, tr("\320\224\320\260\321\202\320\260 \320\270\320\267\320\274\320\265\320\275\320\265\320\275\320\270\321\217"));
		////Дата изменения

		//ui.tableView_files->setModel(&table_model);


		//ui.tableView_files->setColumnWidth(0, 45);
		//ui.tableView_files->setColumnWidth(1, 163);
		//ui.tableView_files->setColumnWidth(2, 210);
		//ui.tableView_files->setColumnWidth(3, 120);
		//ui.tableView_files->setColumnWidth(4, 101);
		//ui.tableView_files->setColumnWidth(5, 195);
		//ui.tableView_files->setColumnWidth(6, 110);



		//selectionModel = ui.tableView_files->selectionModel();

		//connect(selectionModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(OnSelectedParam(QModelIndex,QModelIndex)));

		table_model =new SettingTableModel(this);
		//table_model->setRowStruct();
		ui.tableView_files->setSelectionBehavior(QAbstractItemView::SelectRows);
		ui.tableView_files->setSelectionMode(QAbstractItemView::SingleSelection);
		ui.tableView_files->setStyleSheet("QTableView::item {selection-background-color: rgb(30, 144, 255);selection-color:rgb(255,255,255);} QHeaderView::section { background-color:lightGray }");




		ui.tableView_files->setModel(table_model);
		selectionModel=ui.tableView_files->selectionModel();

		ui.tableView_files->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);
		ui.tableView_files->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
		connect(selectionModel, SIGNAL(currentRowChanged(const QModelIndex&,const QModelIndex&)), this, SLOT(OnSelectedParam(const QModelIndex&,const QModelIndex&)));
		connect(selectionModel,SIGNAL(selectionChanged ( const QItemSelection & , const QItemSelection &  ) ),
			this,SLOT(selectionChanged( const QItemSelection & , const QItemSelection &  )));
		connect(ui.pushButt_dir, SIGNAL(clicked()), this, SLOT(OnButtDir()));
		connect(ui.lineEdit_path, SIGNAL(SignalEnterPressed()), this, SLOT(OnSetPath()));


		ui.ed_num_par->set_num_dig(NUM_DIG_QUINT16);
		ui.ed_num_par->set_new_value(selected_par);
		ui.ed_num_par->set_min_max(1, MAX_QUINT16);
		ui.ed_num_par->set_ena_enter_on_off(true);
		ui.ed_num_par->show_par();

		connect(ui.ed_num_par, SIGNAL(param_changed()), this, SLOT(select_new_param()));
		connect(ui.ed_num_par, SIGNAL(on_off()), this, SLOT(accept()));

	}

DialLoadSavePar::~DialLoadSavePar()
{
	disconnect(selectionModel, SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
	      this, SLOT(OnSelectedParam(QModelIndex,QModelIndex)));
}


void DialLoadSavePar::SetSaveMode(const bool new_save_mode, const bool setup_mode)
{
	save_mode = new_save_mode;
}

void  DialLoadSavePar::set_path(const QString& path)
{
	DirName=path;
	ui.lineEdit_path->setText(DirName);
}

QString  DialLoadSavePar::get_path()
{
	return ui.lineEdit_path->text();
}
void  DialLoadSavePar::set_num_par(const int  num_par)
{
	selected_par = num_par;
	ui.ed_num_par->set_new_value(num_par);
	ui.ed_num_par->show_par();
}
int  DialLoadSavePar::get_num_par()
{
	return selected_par;
}
void  DialLoadSavePar::set_butt_text(const QString& text)
{
	ui.okButton->setText(text);
}



void DialLoadSavePar::OnButtDir() 
{ 
	QFileDialog dial_directory(this);

	dial_directory.setFileMode(QFileDialog::Directory);
	dial_directory.setDirectory(DirName);
	dial_directory.setOption(QFileDialog::ShowDirsOnly, false);
	dial_directory.setOption(QFileDialog::DontUseNativeDialog, true);
	dial_directory.setNameFilter("*.dpm");
	dial_directory.setLabelText(QFileDialog::Reject, tr("\320\236\321\202\320\274\320\265\320\275\320\260"));//Отмена

	dial_directory.setWindowTitle(tr("\320\240\320\260\320\261\320\276\321\207\320\260\321\217 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217"));
	//Рабочая директория
	dial_directory.show();
	if(dial_directory.exec())
	{
		QStringList temp = dial_directory.selectedFiles();
		DirName = temp[0];
		ui.lineEdit_path->setText(DirName);

		CollectParamFiles();
		setSelectedPar();
	}
}


void  DialLoadSavePar::set_ip(const QString& ip)
{
	curr_ip = ip;
	ui.label_ip->setText(ip);
}




void DialLoadSavePar::OnSetPath()
{
	DirName=ui.lineEdit_path->text();
	CollectParamFiles();
}





void DialLoadSavePar::CollectParamFiles()
{
	//QDir directory0(DirName);
	//QFileInfoList  file_list0 = directory0.entryInfoList(QDir::Files);

	//QString ip_num = curr_ip.section('.', -1);


	//const char *spark_metka(DEVICE_METKA);
	//char check_metka[sizeof(DEVICE_METKA)];

	//QString dim_par_name=tr("%1 \321\205 (%2 -%3% +%4%)");//%1 х (%2 -%3% +%4%)


	//int old_row_cnt = table_model.rowCount();
	//if(old_row_cnt > 0)
	//		table_model.removeRows(0, old_row_cnt);



	//int i = 0;
	//table_model.setRowCount(i);

	//foreach (QFileInfo curr_fileinfo, file_list0)
	//{
	//	if(curr_fileinfo.suffix() == "dpm")
	//	{
	//		QString file_name = curr_fileinfo.baseName();

	//		int param_number = file_name.section('_', 2, 2).toInt();
	//		QFile curr_file(curr_fileinfo.absoluteFilePath());

	//		if(curr_file.open(QIODevice::ReadOnly))
	//		{
	//			bool result = true;

	//			if(curr_file.read(check_metka, sizeof(DEVICE_METKA)) != sizeof(DEVICE_METKA))
	//				result = false;

	//			if(result)
	//				result = !strcmp(spark_metka, check_metka);


	//			par_device_t tmp_par_device;

	//			if(result)
	//			{
	//				if(curr_file.read(reinterpret_cast<char *>(&tmp_par_device), sizeof(par_device_t)) != sizeof(par_device_t))
	//					result = false;
	//			}



	//			if(result)
	//			{
	//				QString str_cr(curr_fileinfo.created().toString(Qt::ISODate));
	//				QString str_mod(curr_fileinfo.lastModified().toString(Qt::ISODate));
	//								
	//				str_cr.replace(10, 1, ' ');
	//				str_cr.replace(4, 1, '.');
	//				str_cr.replace(7, 1, '.');

	//				str_mod.replace(10, 1, ' ');
	//				str_mod.replace(4, 1, '.');
	//				str_mod.replace(7, 1, '.');


	//				table_model.setRowCount(i+1);
	//				table_model.setData( table_model.index(i, 0), param_number);

	//				const par_view_t &view_par = tmp_par_device.view_par;
	//				const par_info_strings_t &strings = view_par.strings;
	//			//	const par_extra_alg_options_t &extra_alg_opt = view_par.extra_alg_opt;


	//				table_model.setData( table_model.index(i, 1), "???????"/*Params::ConvDataToStr(strings.par_info, strings.par_info_len)*/ );


	//				QString param_opt;
	//				//if(extra_alg_opt.max_p_diam == 0)
	//				//	param_opt = tr("\320\242\320\276\320\273\321\211 %1-%2 \320\224\320\270\320\260\320\274 > %3")//Толщ %1-%2 Диам > %3
	//				//											.arg(static_cast<float>(extra_alg_opt.min_p_thick)/COEF_THICK, 0, 'f', 2)
	//				//											.arg(static_cast<float>(extra_alg_opt.max_p_thick)/COEF_THICK, 0, 'f', 2)
	//				//											.arg(static_cast<float>(extra_alg_opt.min_p_diam)/COEF_DIAMETER, 0, 'f', 1);
	//				//else
	//				//	param_opt = tr("\320\242\320\276\320\273\321\211 %1-%2 \320\224\320\270\320\260\320\274 %3-%4")//Толщ %1-%2 Диам %3-%4
	//				//											.arg(static_cast<float>(extra_alg_opt.min_p_thick)/COEF_THICK, 0, 'f', 2)
	//				//											.arg(static_cast<float>(extra_alg_opt.max_p_thick)/COEF_THICK, 0, 'f', 2)
	//				//											.arg(static_cast<float>(extra_alg_opt.min_p_diam)/COEF_DIAMETER, 0, 'f', 1)
	//				//											.arg(static_cast<float>(extra_alg_opt.max_p_diam)/COEF_DIAMETER, 0, 'f', 1);

	//				table_model.setData( table_model.index(i, 2), /*param_opt*/ "?????");

	//				if(tmp_par_device.contr_par.trk_par.cn_list.used_layers & USED_LAYER_THICK)
	//				{
	//					const par_thick_t &thick_par = tmp_par_device.contr_par.thick_par;
	//					if(thick_par.thick_lim_relative)
	//						table_model.setData( table_model.index(i, 3), QString("%2 +%3% -%4%") 
	//												.arg(thick_par.thick * 0.01f, 0, 'f', 2)
	//												.arg(thick_par.thick_lim_rel_pos * 0.1f, 0, 'f', 1)
	//												.arg(thick_par.thick_lim_rel_neg * 0.1f, 0, 'f', 1));
	//					else
	//						table_model.setData( table_model.index(i, 3), QString("%2 +%3 -%4")
	//												.arg(thick_par.thick * 0.01f, 0, 'f', 2)
	//												.arg(thick_par.thick_lim_pos * 0.01f, 0, 'f', 1)
	//												.arg(thick_par.thick_lim_neg * 0.01f, 0, 'f', 1));
	//				}
	//				else
	//					table_model.setData( table_model.index(i, 3), tr("\320\275\320\265 \320\272\320\276\320\275\321\202\321\200\320\276\320\273\320\270\321\200\321\203\320\265\321\202\321\201\321\217") );
	//				//не контролируется

	//				table_model.setData( table_model.index(i, 4), /*Params::ConvDataToStr(strings.block_info, strings.block_info_len)*/ "??????");
	//				table_model.setData( table_model.index(i, 5), 
	//					//tr("\320\221\320\273\320\276\320\272 %1 '%2'").//Блок %1 '%2'
	//					//arg(extra_alg_opt.alg_block).arg(Params::ConvDataToStr(strings.alg_info, strings.alg_info_len)) 
	//					"??????");
	//				table_model.setData( table_model.index(i, 6), str_cr );
	//				table_model.setData( table_model.index(i, 7), str_mod );
	//					
	//				i++;

	//			}
	//			curr_file.close();
	//		}

	//	}
	//}

	//table_model.sort(0);
	table_model->populateModel(QDir(DirName));
}


void DialLoadSavePar::setSelectedPar()
{
	//int index = -1;

	//QList<QStandardItem *> item_list = table_model.findItems(  QString::number(selected_par, 10)  , Qt::MatchExactly, 0);

	//if(item_list.size() > 0)
	//{
	//	index = item_list[0]->index().row();
	//	QModelIndex index_start = table_model.index(index, 0);
	//	QModelIndex index_end = table_model.index(index, table_model.columnCount() - 1);
	//	QItemSelection i_sel(index_start, index_end);
	//	selectionModel->select(i_sel, QItemSelectionModel::ClearAndSelect);
	//	ui.tableView_files->scrollTo(index_start);
	//}
	//else
	//	selectionModel->select(table_model.index(0,0), QItemSelectionModel::Clear);

	//return index;

	QModelIndex index_start = table_model->findSettings(selected_par);
	if(index_start.isValid()){
	QModelIndex index_end = table_model->index(index_start.row(), table_model->columnCount() - 1);
	QItemSelection i_sel(index_start, index_end);
	selectionModel->select(i_sel, QItemSelectionModel::ClearAndSelect);
	}
	else
	{
		selectionModel->clear();
	}
}

void DialLoadSavePar::select_new_param()
{
	if(recursive_select)
		return;
	selected_par=ui.ed_num_par->get_value();
	setSelectedPar();
}

void DialLoadSavePar::OnSelectedParam(QModelIndex index0, QModelIndex index1)
{
 /*   if(!index0.isValid())
		return;

	recursive_select = true;

	selected_par = table_model.item(index0.row(), 0)->text().toInt();
	ui.ed_num_par->show_par();

	recursive_select = false;*/
}
void DialLoadSavePar::selectionChanged( const QItemSelection & item_curr, const QItemSelection & item_prev )
{
	QModelIndexList list_index=item_curr.indexes();
	QModelIndex indx_curr=list_index.value(0);
	 if(!indx_curr.isValid())
		return;

	 selected_par=table_model->data(indx_curr).toInt();
	 
	 ui.ed_num_par->set_new_value(selected_par);
	 ui.ed_num_par->show_par();
	
}