#include "params.h"
#include <string.h>
#include <math.h>
#include <QString>


quint8 calc_step(const quint16 beg_r, const quint16 end_r)
{
	if(end_r <= beg_r)
		return 0;

	quint16 tmp = end_r - beg_r;
	if(tmp < LEN_OSC)
		return 0;
	return static_cast<float>(tmp)*2/LEN_OSC - 1;
}

quint16	calc_endr(const quint16 beg_r, const quint8 step)
{
	return beg_r + (step + 1)*(LEN_OSC/2);
}


const quint8 default_chan_tacts[NUM_CHANS] = {
												0,
												1,
												2,
												3,
												4,
												5,
												6,
												7,

												8,
												9,
												10,
												11,

												12,
												13,
												0,
												1
											};


const quint16 default_chan_us[NUM_CHANS] =	{					// 5 + 3
												0,
												0,
												0,
												0,

												0,
												1,
												1,
												1,

												0,
												0,
												0,
												0,

												0,
												1,
												1,
												1
											};


const quint16 chan_rej[NUM_CHANS] =	{
												TD_DEF_PROD,
												TD_DEF_PROD,
												TD_DEF_PROD,
												TD_DEF_PROD,
												TD_DEF_PROD,
												TD_DEF_PROD,
												TD_DEF_POPER,
												TD_DEF_POPER,
												TD_DEF_POPER,
												TD_DEF_POPER,
												TD_DEF_POPER,
												TD_DEF_POPER,
												TD_TOL_LAM,
												TD_TOL_LAM,
												TD_TOL_LAM,
												TD_TOL_LAM
											};




void Params::SetDefaultDevicePar(par_device_t &par_device)
{
	par_contr_t &contr_par = par_device.contr_par;


	par_trk_t &trk_par = contr_par.trk_par;


	par_izm_t &izm_par = trk_par.izm_par;

	izm_par.num_tacts = NUM_TACTS;
	izm_par.num_izm = NUM_IZM;
	izm_par.num_sum = DEF_NUM_SUM;
	izm_par.num_per_elem = DEF_NUM_PER_EL;

	par_filtr_t &filtr_par = trk_par.filtr_par;
	filtr_par.filtr_defect = DEF_FILTR;
	filtr_par.filtr_thick = DEF_FILTR;


	cn_list_t &cn_list  = trk_par.cn_list;

	cn_list.chan_count = DEF_NUM_CHANS;
	cn_list.used_layers = USED_LAYER_DEF;				// ???


	for(int i = 0; i < NUM_CHANS; i++)
	{
		cn_info_t & cn_info = cn_list.cn_info[i];

		cn_info.ntact = default_chan_tacts[i];
		cn_info.nus = default_chan_us[i];			// номер усилителя
		cn_info.rej = chan_rej[i];					// режим канала

		par_probe_t &probe_par = cn_info.probe_par;

		probe_par.t_pr = DEF_T_PR;				// задержка в призме
		probe_par.alpha = DEF_ALPHA;				// угол ввода
		probe_par.cc = DEF_CC_L;					// скорость звука

		cn_info.a_step_count = DEF_B_SCAN_LEN;
		cn_info.a_k_color = 0;


		memset(cn_info.coord_offset, 0, sizeof(quint16) * NUM_COORD_OFFS);

		cn_info.reff_kus = DEF_KUS;

		for(int j = 0; j < NUM_PROCESS_AREA; j++)
		{
			par_cn_area_process_t &cn_area = cn_info.cn_area[j];

			cn_area.on_cn_area = OFF;
		}

		for(int j = 0; j < NUM_STRBS; j++)
		{
			par_strb_info_t &strb_info = cn_info.strb_info[j];

			strb_info.strb_type = DEF_TYPE_STRB;				// режим строба в канале, тип дефекта который определяется этим стробом
			strb_info.reff_kus = DEF_KUS;					// уровень привязки строба (???)

			strb_info.on_extra_por = OFF;
			strb_info.on_extra_por0 = OFF;

			strb_info.extra_por[0] = DEF_POR2_STRB;	// дополнительные пороги у строба
			strb_info.extra_por[1] = DEF_POR3_STRB;

			strb_info.sub_extra_por[0] = sqrt(static_cast<double>(strb_info.extra_por[0])*DEF_POR_STRB) + 0.5f;
			strb_info.sub_extra_por[1] = sqrt(static_cast<double>(strb_info.extra_por[0])*strb_info.extra_por[1]) + 0.5f;
			strb_info.sub_extra_por[2] = sqrt(1.0*DEF_POR_STRB) + 0.5f;

		}
	}



	for(int i = 0; i < NUM_POW_GENS; i++)
	{
		par_pow_t & pow_gen = trk_par.pow_gen[i];

		pow_gen.on_pow = ON;
		pow_gen.val = DEF_POW_VAL;
	}


	for(int i = 0; i < NUM_TACTS; i++)
	{
		par_takt_t & takt = trk_par.takts[i];

		takt.len_hipow = DEF_LEN_HIPOW;
		takt.len_tact = DEF_LEN_TACT;

		takt.mux_uss = 0;					// заполняется непосредственно в дефектоскопе по us.us_input

		
		for(int j = 0; j < NUM_GENS; j++)
		{
			par_gen_t & gen = takt.gens[j];

			gen.on_gen = OFF;
			gen.len_imp = DEF_LEN_IMP;
		}

		for(int j = 0; j < NUM_USS; j++)
		{
			par_us_t & us = takt.uss[j];

			us.on_us = OFF;

			us.us_input = DEF_US_INPUT;		// us_input выставляется для данного номера усилителя 

			us.rej = DEF_REJ_US;
			us.kus = DEF_KUS;
			us.detpar = DETECT_PAR_PLMIN;

			us.taut = DEF_TT;
			us.tauv = DEF_TV;

			us.beg_r = DEF_B_BEGR;						// развёртка А-скана
			us.step_r = DEF_B_STEPR;					// шаг развёртки А-скана

			for(quint8 k = 0; k < NUM_STRBS; k++)
			{	
				par_strb_t & strb = us.strb[k];

				strb.on_strb = OFF;
				strb.por = DEF_POR_STRB;
				strb.beg = DEF_BEG_STRB + DEF_LEN_STRB * k;		// ???
				strb.len = DEF_LEN_STRB;
			}

			par_vrch_t & vrch = us.vrch;

			vrch.on_vrch = OFF;
			vrch.num_p = 2;
			memset(vrch.time, 0, MAX_NUM_PVRCH * sizeof(quint16));
			memset(vrch.kus, 0, MAX_NUM_PVRCH * sizeof(quint8));
		}
	}

	for(int i = 0; i < NUM_CHANS; i++)				// задание включенных по-умолчанию усилителей
	{
		cn_info_t & cn_info = cn_list.cn_info[i];

		par_us_t &uss = trk_par.takts[cn_info.ntact].uss[cn_info.nus];
		uss.on_us = ON;							// и усилитель

		quint8 sub_cnt_input = i % NUM_INPUTS_BLOCK;

		if(cn_info.nus == 0)							// ???
		{
			if(sub_cnt_input < NUM_INPUTS_0)
				uss.us_input = sub_cnt_input;		// номер входа
			else
				uss.us_input = 0;
		}
		else
		{
			if(sub_cnt_input >= NUM_INPUTS_0)
				uss.us_input = sub_cnt_input;		// номер входа
			else
				uss.us_input = NUM_INPUTS_0;
		}
					
		uss.rej = cn_info.rej & TD_MASK;		// режим усилителя 

		if(uss.rej == TD_TOL_REZ)
			uss.strb[REZ_NO_STROB].on_strb = ON;

		for(quint8 j = 0; j < NUM_STRBS; j++)
			cn_info.strb_info[j].on_extra_por = OFF;
	}

	SetUsedLayers(trk_par);		// только выставление по-умолчанию



	par_thick_t &thick_par = contr_par.thick_par;

	thick_par.thick = DEF_THICK;
	thick_par.thick_lim_relative = OFF;
	thick_par.thick_lim_rel_neg = DEF_THICK_REL_LIM;
	thick_par.thick_lim_rel_pos = DEF_THICK_REL_LIM;
	thick_par.thick_lim_neg = DEF_THICK_ABS_LIM;
	thick_par.thick_lim_pos = DEF_THICK_ABS_LIM;

	
	par_thick_corr_t &tol_corr = contr_par.tol_corr;

	tol_corr.thick_corr = DEF_THICK_CORR;
	tol_corr.dt = DEF_THICK_DT;


	par_thick_rez_t &tol_rez = contr_par.tol_rez;

	tol_rez.spectr_on = OFF;

	tol_rez.spectr_shift = DEF_SPECTR_SHIFT;
	tol_rez.spectr_first_el = DEF_SPECTR_FIRST;
	tol_rez.spectr_length = DEF_SPECTR_LENGTH;

	tol_rez.thick_corr = DEF_THICK_CORR;		// коррекция толщины
	tol_rez.N_rez = DEF_N_REZ;					// номер резонанса


	memset(contr_par.alg, 0, sizeof(par_algorithm_t)*NUM_DEFECTS_AREA);		// по умолчанию алгоритмы не настроены

	contr_par.coef_coord = DEF_COEF_COORD;

	par_vdp_t &vdp_par = contr_par.vdp;			// ВДП

	vdp_par.on_off = OFF;
	vdp_par.speed = DEF_VDP_SPEED;


	contr_par.control_step = DEF_CONTROL_STEP;


	par_view_t &view_par = par_device.view_par;

	view_par.curr_nparam = DEF_NUM_PARAM;		// номер настройки


	for(int i = 0; i < NUM_CHANS; i++)
	{
		view_cn_info_t &view_info = view_par.view_info[i];

		par_axis_mode_t &axis_mode = view_info.axis_mode;
		axis_mode.axis_x_mode = 0;
		axis_mode.axis_y_mode = 0;

		view_info.beg_r = DEF_B_BEGR;						// развёртка для осциллограммы данного усилителя (если принимается)
		view_info.stp_r = DEF_B_STEPR;
		view_info.strb = 0;
		view_info.pvrch = 0;

		view_info.def_gen = i % NUM_INPUTS_BLOCK;		// предпочтительный номер генератора
	}

	for(int i = 0; i < NUM_CHANS; i++)				// задание включенных по-умолчанию генераторов
	{
		cn_info_t & cn_info = cn_list.cn_info[i];
		view_cn_info_t &view_info = view_par.view_info[i];
		trk_par.takts[cn_info.ntact].gens[view_info.def_gen].on_gen = ON;		// генератор
	}

	cn_info_t & base_cn_info = cn_list.cn_info[0];
	view_cn_info_t &base_view_info = view_par.view_info[0];

	quint8 def_n_gen = base_view_info.def_gen;
	view_par.npow = def_n_gen/(NUM_GENS/NUM_POW_GENS);
	view_par.ngen = def_n_gen;


	par_osc_t &osc_par = view_par.osc_par;

	osc_par.ntact = base_cn_info.ntact;
	osc_par.nus = base_cn_info.nus;
	osc_par.curr_beg_r = base_view_info.beg_r;				// развёртка канала	-	аналог ed_param
	osc_par.curr_stp_r = base_view_info.stp_r;
	osc_par.curr_end_r = calc_endr(osc_par.curr_beg_r, osc_par.curr_stp_r);		/// для отображения в окне настроек
	osc_par.curr_strb = base_view_info.strb;				// номер строба
	osc_par.curr_pvrch = base_view_info.pvrch;

	osc_par.rej_osc = ON;


	view_par.nchan = 0;
	view_par.chan_us_edit = OFF;

	view_par.scale_thick_to_limits = OFF;


	par_mab_t &mab_par = view_par.mab_par;

	for(int i = 0; i < NUM_MAB_BLOCKS; i++)
	{
		par_block_t &block = mab_par.block[i];

		block.left_side = (i < 4) ? ON : OFF;
		block.offset_mm = 0;

		for(int j = 0; j < NUM_TRANSDUCERS; j++)
		{
			par_transducer_t &transducer = block.transducer[j];

			transducer.is_on = OFF;
			transducer.is_us = j % 2;
			transducer.input_num = 0;
		}
	}




	par_manual_speed_t &mspeed = view_par.mspeed;
	mspeed.update_interval = DEF_UPDATE_INTERVAL;
	mspeed.time_interval = DEF_TIME_INTERVAL;
	mspeed.normal_speed = DEF_NORMAL_SPEED;



	par_extra_alg_options_t &extra_alg_opt = view_par.extra_alg_opt;

	extra_alg_opt.auto_processing = OFF;
	extra_alg_opt.alg_block = 0;

	extra_alg_opt.min_p_thick = 0;			// по умолчанию настройка не относится ни к каким толщинам
	extra_alg_opt.max_p_thick = 0;

	extra_alg_opt.min_p_diam = 0;			// по умолчанию диаметр не определён
	extra_alg_opt.max_p_diam = 0;


	par_info_strings_t &strings = view_par.strings;

	strings.par_info_len = 0;
	strings.alg_info_len = 0;
	strings.block_info_len = 0;



	par_object_t &object_par = view_par.object_par;

	object_par.diameter = DEF_DIAMETER;
	object_par.cc_l = DEF_CC_L;
	object_par.cc_t = DEF_CC_T;




	par_device.version = DEVICE_PAR_VERSION;


}



void Params::SetUsedLayers(par_trk_t &trk_par)
{
	quint8 used_layers = 0;

	for(quint8 i = 0; i < trk_par.cn_list.chan_count; i++)
	{
		cn_info_t & cn_info = trk_par.cn_list.cn_info[i];
		par_us_t &uss = trk_par.takts[cn_info.ntact].uss[cn_info.nus];

		if(uss.on_us)
		{
			switch(cn_info.rej)
			{
			case TD_DEF:
			case TD_DEF_PROD:
			case TD_DEF_POPER:
				used_layers |= USED_LAYER_DEF;
				break;

			case TD_TOL_LAM:
			case TD_TOL:
			case TD_TOL_REZ:
				used_layers |= USED_LAYER_THICK;
				break;

			case TD_B_SCAN:
			default:;
			}
		}
	}

	trk_par.cn_list.used_layers = used_layers;
}


void Params::ConvStrToData(const QString &in_str, quint8 *str_data, quint8 *str_len)
{
	int temp_str_len = in_str.length();

	if(temp_str_len > (INFO_STRING_MAX_LEN / sizeof(QChar)))
		temp_str_len = INFO_STRING_MAX_LEN / sizeof(QChar);

	*str_len = temp_str_len;
	memcpy(str_data, in_str.data(), temp_str_len*sizeof(QChar));
}

QString Params::ConvDataToStr(const quint8 *str_data, const quint8 str_len)
{
	QString out_str(reinterpret_cast<const QChar *>(str_data), str_len);
	return out_str;
}

