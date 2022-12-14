#include "dialpar.h"
#include <map>
#include<utility>
#include <QMessageBox>
#include <QRegExpValidator>
DialPar::DialPar(QWidget *parent)
	: QDialog(parent),
	_chan_count(NUM_CHANS),
	_old_num_chan(_chan_count),

	_num_tacts(0),
	_old_num_tacts(0),

	_num_per_elem(DEF_NUM_PER_EL),

	_filtr_par(),
	_manual_speed(),
	_coef_coord(DEF_COEF_COORD),
	_temp_vdp_speed(0),
	_us_inputs(NUM_CHANS),
	chan_prop_name("chan_number"),
	was_modified(false)
{
	ui.setupUi(this);


	chan_label_arr[0] = ui.lab_0;
	chan_label_arr[1] = ui.lab_1;
	chan_label_arr[2] = ui.lab_2;
	chan_label_arr[3] = ui.lab_3;
	chan_label_arr[4] = ui.lab_4;
	chan_label_arr[5] = ui.lab_5;
	chan_label_arr[6] = ui.lab_6;
	chan_label_arr[7] = ui.lab_7;
	chan_label_arr[8] = ui.lab_8;
	chan_label_arr[9] = ui.lab_9;
	chan_label_arr[10] = ui.lab_10;
	chan_label_arr[11] = ui.lab_11;
	chan_label_arr[12] = ui.lab_12;
	chan_label_arr[13] = ui.lab_13;
	chan_label_arr[14] = ui.lab_14;
	chan_label_arr[15] = ui.lab_15;


	ed_tact_arr[0] = ui.line_tact0;
	ed_tact_arr[1] = ui.line_tact1;
	ed_tact_arr[2] = ui.line_tact2;
	ed_tact_arr[3] = ui.line_tact3;
	ed_tact_arr[4] = ui.line_tact4;
	ed_tact_arr[5] = ui.line_tact5;
	ed_tact_arr[6] = ui.line_tact6;
	ed_tact_arr[7] = ui.line_tact7;
	ed_tact_arr[8] = ui.line_tact8;
	ed_tact_arr[9] = ui.line_tact9;
	ed_tact_arr[10] = ui.line_tact10;
	ed_tact_arr[11] = ui.line_tact11;
	ed_tact_arr[12] = ui.line_tact12;
	ed_tact_arr[13] = ui.line_tact13;
	ed_tact_arr[14] = ui.line_tact14;
	ed_tact_arr[15] = ui.line_tact15;


	ed_ninp_arr[0] = ui.line_ed_ninp0;
	ed_ninp_arr[1] = ui.line_ed_ninp1;
	ed_ninp_arr[2] = ui.line_ed_ninp2;
	ed_ninp_arr[3] = ui.line_ed_ninp3;
	ed_ninp_arr[4] = ui.line_ed_ninp4;
	ed_ninp_arr[5] = ui.line_ed_ninp5;
	ed_ninp_arr[6] = ui.line_ed_ninp6;
	ed_ninp_arr[7] = ui.line_ed_ninp7;
	ed_ninp_arr[8] = ui.line_ed_ninp8;
	ed_ninp_arr[9] = ui.line_ed_ninp9;
	ed_ninp_arr[10] = ui.line_ed_ninp10;
	ed_ninp_arr[11] = ui.line_ed_ninp11;
	ed_ninp_arr[12] = ui.line_ed_ninp12;
	ed_ninp_arr[13] = ui.line_ed_ninp13;
	ed_ninp_arr[14] = ui.line_ed_ninp14;
	ed_ninp_arr[15] = ui.line_ed_ninp15;


	comb_rej_arr[0] = ui.comboBox_rej0;
	comb_rej_arr[1] = ui.comboBox_rej1;
	comb_rej_arr[2] = ui.comboBox_rej2;
	comb_rej_arr[3] = ui.comboBox_rej3;
	comb_rej_arr[4] = ui.comboBox_rej4;
	comb_rej_arr[5] = ui.comboBox_rej5;
	comb_rej_arr[6] = ui.comboBox_rej6;
	comb_rej_arr[7] = ui.comboBox_rej7;
	comb_rej_arr[8] = ui.comboBox_rej8;
	comb_rej_arr[9] = ui.comboBox_rej9;
	comb_rej_arr[10] = ui.comboBox_rej10;
	comb_rej_arr[11] = ui.comboBox_rej11;
	comb_rej_arr[12] = ui.comboBox_rej12;
	comb_rej_arr[13] = ui.comboBox_rej13;
	comb_rej_arr[14] = ui.comboBox_rej14;
	comb_rej_arr[15] = ui.comboBox_rej15;


	ui.line_num_chan->set_num_dig(NUM_DIG_NCHAN);
	//ui.line_num_chan->set_new_value(_chan_count);
	ui.line_num_chan->set_min_max(MIN_CHAN_COUNT, MAX_CHAN_COUNT);
	connect(ui.line_num_chan, SIGNAL(param_changed()), this, SLOT(chan_count_changed()));




	ui.line_num_tacts->set_num_dig(NUM_DIG_NTACT);
	//	ui.line_num_tacts->set_new_value(_num_tacts);
	ui.line_num_tacts->set_min_max(MIN_NUM_TACTS, NUM_TACTS);
	connect(ui.line_num_tacts, SIGNAL(param_changed()), this, SLOT(tact_number_changed()));


	ui.line_num_per_elem->set_num_dig(NUM_DIG_NTACT);
	//	ui.line_num_per_elem->set_new_value(_num_per_elem);
	ui.line_num_per_elem->set_min_max(MIN_NUM_PER_EL, MAX_NUM_PER_EL);



	for(quint8 i=0;i<NUM_CHANS;i++)
	{
		(ed_tact_arr[i])->set_num_dig(NUM_DIG_NTACT);
		/*	(ed_tact_arr[i])->set_data(&local_cn_info[i].ntact);*/
		(ed_tact_arr[i])->set_min_max(MIN_NUM_TACT, MAX_NUM_TACT);	// при изменении количества тактов перезадаЄтс€
		(ed_tact_arr[i])->set_shift(1);

		(ed_ninp_arr[i])->set_num_dig(NUM_DIG_INPUTS);
		/*	(ed_ninp_arr[i])->set_data(input_us + i);	*/
		(ed_ninp_arr[i])->set_min_max(MIN_NUM_INPUTS, MAX_NUM_INPUTS);
		(ed_ninp_arr[i])->set_shift(1);
		(ed_ninp_arr[i])->setProperty(chan_prop_name,i);
		connect(ed_ninp_arr[i], SIGNAL(param_changed()), this, SLOT(ninp_changed()));
	}




	ui.line_filtr_def->set_num_dig(NUM_DIG_FILTR);
	/*ui.line_filtr_def->set_data(&filtr_par.filtr_defect);*/
	ui.line_filtr_def->set_min_max(MIN_FILTR,MAX_FILTR);

	ui.line_filtr_thick->set_num_dig(NUM_DIG_FILTR);
	/*ui.line_filtr_thick->set_data(&filtr_par.filtr_thick);*/
	ui.line_filtr_thick->set_min_max(MIN_FILTR,MAX_FILTR);




	ui.ed_normal_speed->set_num_dig(NUM_DIG_SPEED);
	/*ui.ed_normal_speed->set_data(&manual_speed.normal_speed);*/	
	ui.ed_normal_speed->set_min_max(MIN_NORMAL_SPEED, MAX_NORMAL_SPEED);
	ui.ed_normal_speed->set_coeff(COEF_NORMAL_SPEED);

	ui.ed_update_interval->set_num_dig(NUM_DIG_INTERVAL);
	/*ui.ed_update_interval->set_data(&manual_speed.update_interval);	*/
	ui.ed_update_interval->set_min_max(MIN_UPDATE_INTERVAL, MAX_UPDATE_INTERVAL);
	ui.ed_update_interval->set_coeff(COEF_INTERVAL);
	connect(ui.ed_update_interval, SIGNAL(param_changed()), this, SLOT(update_interval_changed()));

	ui.ed_time_interval->set_num_dig(NUM_DIG_INTERVAL);
	/*ui.ed_time_interval->set_data(&manual_speed.time_interval);	*/
	ui.ed_time_interval->set_min_max(MIN_TIME_INTERVAL, MAX_TIME_INTERVAL);
	ui.ed_time_interval->set_coeff(COEF_INTERVAL);
	connect(ui.ed_time_interval, SIGNAL(param_changed()), this, SLOT(time_interval_changed()));


	ui.ed_coef_coord->set_num_dig(NUM_DIG_COEF_COORD);
	//ui.ed_coef_coord->set_data(&coef_coord);
	ui.ed_coef_coord->set_coeff(COEF_COEF_COORD);
	ui.ed_coef_coord->set_min_max(MIN_COEF_COORD, MAX_COEF_COORD);


	ui.ed_vdp->set_num_dig(NUM_DIG_VDP_SPEED);
	/*ui.ed_vdp->set_data(&temp_vdp_speed);*/
	ui.ed_vdp->set_coeff(COEF_VDP_SPEED);
	ui.ed_vdp->set_min_max(MIN_VDP_SPEED, MAX_VDP_SPEED);






	connect(ui.pushButton_colors, SIGNAL(clicked()), parent, SLOT(changeColors()));

	QList<QWidget *> widgets = parent->findChildren<QWidget *>();
	QList<QWidget *>::iterator it = std::find_if(widgets.begin(), widgets.end(),
		[](QWidget *widget) -> bool {
			return (qstrcmp(widget->metaObject()->className(),"OscillogramWidget") == 0);

	});
	if(it!=widgets.end())
	{

		connect(ui.checkBox_axis_x_mm, SIGNAL(clicked(bool)), *it, SLOT(change_AxisXcapt(bool)));				// переноситс€ в настройки каналов ???
		connect(ui.checkBox_logarithm_capt, SIGNAL(clicked(bool)), *it, SLOT(change_LogCaption(bool)));
	}


	connect(ui.checkBox_vdp, SIGNAL(clicked()), this, SLOT(VDP_changed()));

	QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
	QRegExp ipRegex ("^" + ipRange
                 + "\\." + ipRange
                 + "\\." + ipRange
                 + "\\." + ipRange + "$");
	QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
	ui.lineEdit_ip->setValidator(ipValidator);
	ui.lineEdit_ip->setInputMask("000.000.000.000");
	ui.lineEdit_ip->setCursorPosition(0);

	QRegExp zond_freqRegex=QRegExp("[0-9]");
	QRegExpValidator *zond_freqValidator = new QRegExpValidator(zond_freqRegex, this);
	ui.line_zond_freq->setValidator(zond_freqValidator);
	ui.line_zond_freq->setInputMask("0000");
}

DialPar::~DialPar()
{

}
//*******************slots************************************************
void DialPar::VDP_changed()
{
	ui.ed_vdp->setEnabled(ui.checkBox_vdp->isChecked() && ui.ed_coef_coord->isEnabled());

}
void DialPar::ninp_changed()
{

	int chan = -1;

	chan=sender()->property(chan_prop_name).toInt();// определение, какой усилитель переключен
	if ((chan < 0)||(chan > NUM_CHANS))
		return;
	quint8 new_us=get_us_from_input(_us_inputs[chan]);
	
	_local_cn_info[chan].nus=new_us;
}

void DialPar::chan_count_changed()
{

	_chan_count=ui.line_num_chan->get_value();


	show_enabled_chanals();
}
void DialPar::tact_number_changed()
{
	_num_tacts=ui.line_num_tacts->get_value();
	for(quint8 i=0;i<NUM_CHANS;i++)
	{
		(ed_tact_arr[i])->set_min_max(MIN_NUM_TACT, _num_tacts - 1);
		(ed_tact_arr[i])->apply_current();
	}
	
	_old_num_tacts = _num_tacts;
}
void DialPar::update_interval_changed()
{
}
void DialPar::time_interval_changed()
{
	_manual_speed.time_interval=ui.ed_time_interval->get_value();
	if((_manual_speed.time_interval % _manual_speed.update_interval) != 0)
	{
		if( (_manual_speed.time_interval % _manual_speed.update_interval) > _manual_speed.update_interval/2 )
			_manual_speed.time_interval += _manual_speed.update_interval - (_manual_speed.time_interval % _manual_speed.update_interval);
		else
			_manual_speed.time_interval -= _manual_speed.time_interval % _manual_speed.update_interval;


		if(_manual_speed.time_interval < _manual_speed.update_interval)
			_manual_speed.time_interval = _manual_speed.update_interval;

		ui.ed_time_interval->set_new_value(_manual_speed.time_interval);

		ui.ed_time_interval->show_par();
	}
}

//***********************end slots**************************************

int DialPar::index_for_us_rej(const quint8 rej)
{
	int result = 0;
	switch(rej)
	{
	case TD_DEF_PROD:
		result = 0;
		break;

	case TD_DEF_POPER:
		result = 1;
		break;

	case TD_TOL_LAM:
		result = 2;
		break;

	case TD_B_SCAN:
		result = 3;
		break;

	case TD_TOL:
		result = 4;
		break;

	case TD_TOL_REZ:
		result = 5;
		break;

	}
	return result;
}
quint8 DialPar::us_rej_of_index(const int index)
{
	quint8 result = TD_DEF_PROD;
	switch(index)
	{
	case 0:
		result = TD_DEF_PROD;
		break;

	case 1:
		result = TD_DEF_POPER;
		break;

	case 2:
		result = TD_TOL_LAM;
		break;

	case 3:
		result = TD_B_SCAN;
		break;

	case 4:
		result = TD_TOL;
		break;

	case 5:
		result = TD_TOL_REZ;
		break;
	}
	return result;
}
quint8 DialPar::get_us_from_input(const quint8 input) const
{
	if(input < NUM_INPUTS_0)	// используетс€ 2 усилител€, оба по 5 выходов
		return 0;

	return 1;
}

void DialPar::show_enabled_chanals()
{
	for(quint8 i = 0; i < NUM_CHANS; i++)
	{
		const bool visible = i < _chan_count;
		(chan_label_arr[i])->setVisible(visible);
		(ed_tact_arr[i])->setVisible(visible);
		(ed_ninp_arr[i])->setVisible(visible);
		(comb_rej_arr[i])->setVisible(visible);
	}

	bool snd_prt_visible = (_chan_count > (NUM_CHANS/2));

	ui.lab_chans_2->setVisible(snd_prt_visible);
	ui.lab_ninp_2->setVisible(snd_prt_visible);
	ui.lab_tacts_2->setVisible(snd_prt_visible);
	ui.lab_rej_2->setVisible(snd_prt_visible);
}

void DialPar::set_chans(const par_izm_t &izm_par, const cn_list_t& cn_list, const std::vector<quint8>& us_inputs)
{
	memcpy(_local_cn_info, cn_list.cn_info, sizeof(cn_info_t)*NUM_CHANS);
	_us_inputs.assign(us_inputs.begin(),us_inputs.end());

	_chan_count = cn_list.chan_count;
	_old_num_chan=_chan_count;
	ui.line_num_chan->set_new_value(_chan_count);
	ui.line_num_chan->show_par();

	show_enabled_chanals();

	_num_tacts = izm_par.num_tacts;
	_old_num_tacts = _num_tacts;
	ui.line_num_tacts->set_new_value(_num_tacts);
	ui.line_num_tacts->show_par();

	_num_per_elem = izm_par.num_per_elem;
	ui.line_num_per_elem->set_new_value(_num_per_elem);
	ui.line_num_per_elem->show_par();

	for(quint8 i=0;i<NUM_CHANS;i++)
	{
		(ed_tact_arr[i])->set_min_max(MIN_NUM_TACT, _num_tacts - 1);
		(ed_tact_arr[i])->set_new_value(_local_cn_info[i].ntact);
		(ed_tact_arr[i])->show_par();

		(ed_ninp_arr[i])->set_new_value(_us_inputs[i]);
		(ed_ninp_arr[i])->show_par();

		_local_cn_info[i].nus = get_us_from_input(_us_inputs[i]);

		(comb_rej_arr[i])->setCurrentIndex(index_for_us_rej(_local_cn_info[i].rej));
	}
}

void DialPar::get_chans(std::vector<std::tuple<quint8,quint8,quint8>>& chan_info,std::vector<quint8>& us_inputs)
{
	apply_chan_params();

	for(quint8 i=0;i<NUM_CHANS;i++)
	{
		quint8 rej=us_rej_of_index(comb_rej_arr[i]->currentIndex());
		if(rej!=_local_cn_info[i].rej)
			was_modified=true;
		chan_info.push_back(std::make_tuple(_local_cn_info[i].ntact,_local_cn_info[i].nus,rej));
		/*out_cn_info[i].nus = local_cn_info[i].nus;
		out_cn_info[i].ntact = local_cn_info[i].ntact;
		out_cn_info[i].rej = us_rej_of_index((*comb_rej_arr[i])->currentIndex());*/
	}
	us_inputs.assign(_us_inputs.begin(),_us_inputs.end());
	//memcpy(out_input, input_us, sizeof(quint8)*NUM_CHANS);
}
quint8 DialPar::get_num_tacts()
{
	ui.line_num_tacts->apply_current();	
	_num_tacts =(quint8) ui.line_num_tacts->get_value();
	return _num_tacts;
}

quint8 DialPar::get_num_chans()
{
	ui.line_num_chan->apply_current();
	_chan_count=ui.line_num_chan->get_value();
	return _chan_count;
}

quint8 DialPar::get_number_per_element()
{
	ui.line_num_per_elem->apply_current();
	_num_per_elem=ui.line_num_per_elem->get_value();
	return _num_per_elem;
}

void DialPar::set_conn_settings(const QString &new_ip_addr)
{
	ui.lineEdit_ip->setText(new_ip_addr);
}
QString DialPar::get_conn_settings() const
{
	return ui.lineEdit_ip->text();
}
void  DialPar::set_zond_freq(int freq)
{
	ui.line_zond_freq->setText(QString::number(freq, 10));
}
int DialPar::get_zond_freq() const 
{
	int new_freq = ui.line_zond_freq->text().toInt();
	if((new_freq >= MIN_ZOND_FREQ) && (new_freq <= MAX_ZOND_FREQ))
	{
		return new_freq;

	}
	return -1;
}

void DialPar::set_filtr_par(const par_filtr_t &in_filtr_par)
{
	memcpy(&_filtr_par, &in_filtr_par, sizeof(par_filtr_t));

	ui.line_filtr_def->set_new_value(_filtr_par.filtr_defect);
	ui.line_filtr_def->show_par();

	ui.line_filtr_thick->set_new_value(_filtr_par.filtr_thick);
	ui.line_filtr_thick->show_par();
}
void DialPar::get_filtr_par(par_filtr_t& out_filtr_par)
{
	ui.line_filtr_def->apply_current();
	_filtr_par.filtr_defect=ui.line_filtr_def->get_value();

	ui.line_filtr_thick->apply_current();
	_filtr_par.filtr_thick=ui.line_filtr_thick->get_value();

	memcpy(&out_filtr_par, &_filtr_par, sizeof(par_filtr_t));
}
void DialPar::set_control_step(const quint8 in_control_step)
{
	auto index_for_control_step=[](const quint8 step)->int
	{
		int result = 0;
		switch(step)
		{
		case 1:
			result = 0;
			break;

		case 2:
			result = 1;
			break;

		case 5:
			result = 2;
			break;

		case 10:
			result = 3;
			break;

		default:
			result = 0;
		}
		return result;
	};

	ui.comboBox_resolution_koef->setCurrentIndex(index_for_control_step(in_control_step));

}
quint8 DialPar::get_control_step() const
{
	auto control_step_of_index=[](const int index)->quint8
	{
		quint8 result = 1;
		switch(index)
		{
		case 0:
			result = 1;
			break;

		case 1:
			result = 2;
			break;

		case 2:
			result = 5;
			break;

		case 3:
			result = 10;
			break;
		}
		return result;
	};

	return control_step_of_index(ui.comboBox_resolution_koef->currentIndex());
}
void DialPar::set_axis_modes(DeviceSettings* device_settings)
{
	const view_cn_info_t* p_view_info = device_settings->getChanViewInfoPtr(0);
	const par_axis_mode_t &axis_mode0 = p_view_info->axis_mode;
	ui.checkBox_axis_x_mm->setChecked(axis_mode0.axis_x_mode);
	ui.checkBox_logarithm_capt->setChecked(axis_mode0.axis_y_mode);
}
void DialPar::set_layer_flags(const quint8 flags)
{

	ui.checkBox_layer_0->setChecked(flags & USED_LAYER_0);
	ui.checkBox_layer_1->setChecked(flags & USED_LAYER_1);
	ui.checkBox_layer_2->setChecked(flags & USED_LAYER_2);
	ui.checkBox_layer_thick->setChecked(flags & USED_LAYER_THICK);
}
quint8 DialPar::get_layer_flags() const
{
	quint8 flags = 0;

	if(ui.checkBox_layer_0->isChecked())
		flags |= USED_LAYER_0;

	if(ui.checkBox_layer_1->isChecked())
		flags |= USED_LAYER_1;

	if(ui.checkBox_layer_2->isChecked())
		flags |= USED_LAYER_2;

	if(ui.checkBox_layer_thick->isChecked())
		flags |= USED_LAYER_THICK;

	return flags;
}
void DialPar::set_manual_speed(const par_manual_speed_t &in_manual_speed)
{
	memcpy(&_manual_speed, &in_manual_speed, sizeof(par_manual_speed_t));

	ui.ed_normal_speed->set_new_value(_manual_speed.normal_speed);
	ui.ed_normal_speed->show_par();

	ui.ed_update_interval->set_new_value(_manual_speed.update_interval);
	ui.ed_update_interval->show_par();

	ui.ed_time_interval->set_new_value(_manual_speed.time_interval);
	ui.ed_time_interval->show_par();

	ui.ed_time_interval->set_inc_step(_manual_speed.update_interval);
}
void DialPar::get_manual_speed(par_manual_speed_t& out_manual_speed) 
{


	ui.ed_normal_speed->apply_current();
	_manual_speed.normal_speed=ui.ed_normal_speed->get_value();


	ui.ed_update_interval->apply_current();
	_manual_speed.update_interval=ui.ed_update_interval->get_value();

	ui.ed_time_interval->apply_current();
	_manual_speed.time_interval=ui.ed_time_interval->get_value();

	if((_manual_speed.time_interval % _manual_speed.update_interval) != 0)
	{
		if( (_manual_speed.time_interval % _manual_speed.update_interval) > _manual_speed.update_interval/2 )
			_manual_speed.time_interval += _manual_speed.update_interval - (_manual_speed.time_interval % _manual_speed.update_interval);
		else
			_manual_speed.time_interval -= _manual_speed.time_interval % _manual_speed.update_interval;


		if(_manual_speed.time_interval < _manual_speed.update_interval)
			_manual_speed.time_interval = _manual_speed.update_interval;


	}

	memcpy(&out_manual_speed, &_manual_speed, sizeof(par_manual_speed_t));
}
void DialPar::set_coef_coord(const quint16 in_coef_coord)
{
	_coef_coord = in_coef_coord;
	ui.ed_coef_coord->set_new_value(_coef_coord);
	ui.ed_coef_coord->show_par();
}
quint16 DialPar::get_coef_coord() const
{
	ui.ed_coef_coord->apply_current();
	return ui.ed_coef_coord->get_value();
}

void DialPar::set_string_par(const par_info_strings_t &in_str_par)
{
	ui.lineEdit_setting_name->setText(DeviceSettings::ConvRawArrayToStr(in_str_par.par_info, in_str_par.par_info_len));
}

void DialPar::get_string_par(par_info_strings_t *out_str_par)
{
	DeviceSettings::ConvStrToRawArray(ui.lineEdit_setting_name->text(), out_str_par->par_info, &out_str_par->par_info_len);
}

void DialPar::set_vdp_param(const par_vdp_t &in_vdp)
{
	_temp_vdp_speed = in_vdp.speed;
	ui.ed_vdp->set_new_value(_temp_vdp_speed);
	ui.ed_vdp->show_par();

	ui.checkBox_vdp->setChecked(in_vdp.on_off);
	ui.ed_vdp->setEnabled(in_vdp.on_off && ui.ed_coef_coord->isEnabled());
}

void DialPar::get_vdp_param(par_vdp_t *out_vdp)
{
	out_vdp->on_off = ui.checkBox_vdp->isChecked() ? ON : OFF;

	ui.ed_vdp->apply_current();
	_temp_vdp_speed=ui.ed_vdp->get_value();
	out_vdp->speed = _temp_vdp_speed;
}
void DialPar::enable_params(const bool is_enable)
{
	ui.line_zond_freq->setEnabled(is_enable);

	ui.line_num_chan->setEnabled(is_enable);
	ui.line_num_tacts->setEnabled(is_enable);
	ui.line_num_per_elem->setEnabled(is_enable);

	for(quint8 i=0;i<NUM_CHANS;i++)
	{
		(ed_tact_arr[i])->setEnabled(is_enable);
		(ed_ninp_arr[i])->setEnabled(is_enable);
		(comb_rej_arr[i])->setEnabled(is_enable);
	}


	ui.line_filtr_def->setEnabled(is_enable);
	ui.line_filtr_thick->setEnabled(is_enable);

	ui.comboBox_resolution_koef->setEnabled(is_enable);

	ui.ed_normal_speed->setEnabled(is_enable);
	ui.ed_update_interval->setEnabled(is_enable);
	ui.ed_time_interval->setEnabled(is_enable);


	ui.checkBox_layer_0->setEnabled(is_enable);
	ui.checkBox_layer_1->setEnabled(is_enable);
	ui.checkBox_layer_2->setEnabled(is_enable);
	ui.checkBox_layer_thick->setEnabled(is_enable);

	ui.lineEdit_setting_name->setEnabled(is_enable);

	ui.ed_coef_coord->setEnabled(is_enable);

	ui.checkBox_vdp->setEnabled(is_enable);
	ui.ed_vdp->setEnabled(ui.checkBox_vdp->isChecked() && is_enable);
}
void DialPar::apply_chan_params()
{
	typedef std::map<int,std::pair<int,int>> chan_map;

	auto get_dublicate=[](const chan_map& source_map)->chan_map
	{

		chan_map m2(source_map);
		chan_map dub_map;

		for (auto pos = source_map.begin(); pos != source_map.end(); ++pos)
		{
			int counter = 0;

			counter = std::count_if(m2.begin(), m2.end(), [&]( const std::pair<int,std::pair<int,int>>&   val) {return((pos->second.first == val.second.first) && (pos->second.second == val.second.second)); });
			if (counter > 1)
			{
				dub_map.insert(*pos);
			}
		}
		return dub_map;
	};

	chan_map ch_map;

	ui.line_num_tacts->apply_current();	
	_num_tacts=ui.line_num_tacts->get_value();

	if(_num_tacts != _old_num_tacts)
	{
		tact_number_changed();
		was_modified=true;
	}
	if(_chan_count!=_old_num_chan)
		was_modified=true;

	for(quint8 i=0;i<NUM_CHANS;i++)
	{
		(ed_tact_arr[i])->apply_current();
		quint8 new_tact=ed_tact_arr[i]->get_value();
		if(_local_cn_info[i].ntact!=new_tact)
			was_modified=true;
		_local_cn_info[i].ntact=new_tact;
		(ed_ninp_arr[i])->apply_current();
		
		_us_inputs[i]=ed_ninp_arr[i]->get_value();
		quint8 new_us=get_us_from_input(_us_inputs[i]);
		if(_local_cn_info[i].nus!= new_us)
			was_modified=true;
		_local_cn_info[i].nus = new_us;

		auto tact_us=std::make_pair(_local_cn_info[i].ntact,_local_cn_info[i].nus);
		auto chan_value=std::make_pair(i,tact_us);
		ch_map.insert(chan_value);

	}


	chan_map dublicate_map=	get_dublicate(ch_map);

	if(dublicate_map.size()>0)
	{
		int chan1 =dublicate_map.begin()->first;
		int chan2=(++dublicate_map.begin())->first;
		int tact=_local_cn_info[chan1].ntact;
		QString message=tr("\320\222 \320\272\320\260\320\275\320\260\320\273\320\260\321\205 %1 \320\270 %2 \320\262 \320\276\320\264\320\275\320\276\320\274 \320\270 \321\202\320\276\320\274 \320\266\320\265 \321\202\320\260\320\272\321\202\320\265 %3 \321\203\320\272\320\260\320\267\320\260\320\275\321\213 \321\203\321\201\320\270\320\273\320\270\321\202\320\265\320\273\320\270 %4 \320\270 %5, \n\321\207\321\202\320\276 \320\275\320\265\320\264\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\276. "
			"\320\222 \320\276\320\264\320\275\320\276\320\274 \321\202\320\260\320\272\321\202\320\265 \320\274\320\276\320\266\320\275\320\276 \321\203\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276 \320\277\320\276 \320\276\320\264\320\275\320\276\320\274\321\203 \321\203\321\201\320\270\320\273\320\270\321\202\320\265\320\273\321\216 \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275\320\260 1-5 \320\270 \320\264\320\270\320\260\320\277\320\260\320\267\320\276\320\275\320\260 6-10.")
			/*
			¬ каналах %1 и %2 в одном и том же такте %3 указаны усилители %4 и %5, 
			что недопустимо. ¬ одном такте можно указывать только по одному усилителю диапазона 1-5 и диапазона 6-10.
			*/
			.arg(chan2+1).arg(chan1+1).arg(tact+1).arg(_us_inputs[chan2]+1).arg(_us_inputs[chan1]+1);
		throw BadInputException(message.toStdString());
	}

}
void DialPar::accept()
{

	try
	{
		apply_chan_params();
		QDialog::accept();
	}
	catch(BadInputException& ex)
	{
		QString err_message(ex.what());
		QMessageBox::warning(this,	tr("\320\232\320\276\320\275\321\204\320\273\320\270\320\272\321\202 \320\272\320\260\320\275\320\260\320\273\320\276\320\262"),
			// онфликт каналов
			err_message);
		return;
	}
}
bool DialPar::modified()const
{
	return this->was_modified;
}
void DialPar::showEvent(QShowEvent * _event)
{
	QDialog::showEvent(_event);
	was_modified=false;
}
