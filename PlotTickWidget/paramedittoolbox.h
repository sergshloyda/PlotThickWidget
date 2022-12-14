#ifndef PARAMEDITTOOLBOX_H
#define PARAMEDITTOOLBOX_H

#include <QWidget>
#include "ui_ParamEditToolBar.h"
#include "mainmenu.h"
#include "widgetselector.h"
#include "devicesettings.h"
#include "qmap.h"

#define NGEN_BG_COLOR "rgb(250, 250, 250)"
#define NGEN_ON_COLOR "rgb(250, 0, 0)"
#define NGEN_OFF_COLOR "rgb(0, 0, 0)"


#define NUS_BG_COLOR "rgb(250, 250, 250)"
#define NUS_ON_COLOR "rgb(0, 140, 0)"
#define NUS_OFF_COLOR "rgb(0, 0, 0)"


#define NSTROB_BG_COLOR "rgb(250, 250, 250)"
#define NSTROB_ON_COLOR "rgb(217, 0, 108)"
#define NSTROB_OFF_COLOR "rgb(180, 180, 180)"

class PlotTickWidget;
class ParamEditToolBox : public QWidget
{
	Q_OBJECT

public:
	ParamEditToolBox(QWidget *parent,DeviceSettings* p_dev_settings);
	~ParamEditToolBox();
	enum StrobType{
		StrobSupervisor=0,
		StrobDefIn=1,
		StrobDefMid=2,
		StrobDefOut=3,
		StrobLamin=4,
		StrobThick=5,
		StrobRez=6
	};

	static bool is_strb_multilevel(const cn_info_t &cn_info);

	void init_ed_params();
	
	void apply_new_settings();
	void update_param_edit();


	void show_on_gens();
	void show_on_uss();
	void switch_strob_extra_por(const bool extra_por_en, const bool extra_por);
	void switch_strob_b_scan(const bool b_scan);

	void apply_paste_edit();
	void apply_param_pos_edit();
	void apply_channals_states();
	void apply_chan();
	void update_chan();
	void apply_strob_extra_por();
	void apply_us_rej();
	void apply_strob_extra_por_a();
	void apply_chan_us_set();
	void apply_tact();
	void update_tact();
	void apply_ninp_us();
	void apply_us_on();
	void apply_detpar();
	void apply_begr();
	void update_begr();
	void apply_endr();
	void apply_ngen();
	void apply_gen_on();
	void apply_len_imp();
	void apply_npow();
	void apply_vpow();
	void apply_kus();
	void apply_rej();
	void apply_tt();
	void apply_tv();
	void apply_nstrob();
	void apply_strob_on();
	void apply_strob_type();

	void apply_por();
	void update_por();

	void apply_por2();
	void update_por2();

	void apply_por3();
	void update_por3();

	void apply_bstr();
	void update_bstr();

	void apply_lstr();
	void update_lstr();

	void apply_b_stepr();
	void apply_b_por();
	void apply_b_begr();
	void apply_b_count();
	void apply_avi_nump_vrch();

	void apply_curr_np_vrch();
	void update_curr_np_vrch();

	void apply_timev();
	void update_timev();

	void apply_kusv();
	void update_kusv();

	void apply_onvrch();
	void apply_vrch_visible();
	void apply_nump_vrch();
	void apply_thick_corr_par();
	void apply_luch_par();

	void apply_scale_mode();

	void set_param_pos_edit(const bool initing = false);
	void set_chan_us_set();
	void set_tact_limits();
	void set_tact_params();
	void set_us_params();
	void set_gen_params();
	void set_strob_params();
	void set_rez_strob_bstr();
	void set_rez_strob_lstr();
	void set_extra_strob_params();
	void set_b_scan_params();
	void set_vrch_params();
	void set_avi_nump_vrch();
	void set_curr_np_vrch();
	void set_vrch_point();
	void select_obj_par_button();
	
	QLabel* getLabelConn();

public slots:
	void chan_changed();
	void tact_changed();
	void ninp_us_changed();
	void detpar_slot(int index);
	void begr_changed();
	void endr_changed();
	void endr_result_changed();
	void kus_changed();
	void tt_changed();
	void tv_changed();
	void nstrob_changed();
	void slot_strob_on_off();
	void por_changed();
	void bstrob_changed();
	void lstrob_changed();
	void extra_strob_toggled(bool extra_set);
	void por2_changed();
	void por3_changed();
	void b_stepr_changed();
	void b_stepr_result_changed();
	void b_por_changed();
	void b_begr_changed();
	void b_count_changed();
	void b_count_result_changed();
	void vron_changed();
	void numpv_changed();
	void npov_changed();
	void vtime_changed();
	void vkus_changed();
	void ngen_changed();
	void leni_changed();
	void thick_corr_changed();
	void thick_dt_changed();
	void thick_n_rez__changed();
	void t_pr_changed();
	void cc_changed();
	void alpha_changed();


	void param_set_pos_edit(const bool pos_edit);
	/*void extra_por_2_changed();
	void extra_por_3_changed();*/
	void slot_chan_us_set(bool chan_us_set);
	void rej_slot(int);
	void slot_us_on_off();
	void slot_gen_on_off();
	void npow_slot(int npow);
	void vpow_slot(int index);
	void scale_mode_slot(bool);

	void copy_us_params();
	void paste_us_params();

	void change_curr_strob();
	void change_strob_length();
	void change_strob_porog();
	void change_strob_begin();
	void change_osc_range();
	void change_strob_porog2();
	void change_strob_porog3();
	void change_num_p_VRCH();
	void change_param_p_VRCH();
signals:
		void EditToggled();
private:
	
	MainMenu* _main_menu;
	PlotTickWidget* _main_widget;
	WidgetSelector _widget_selector;
	DeviceSettings * _curr_par_device;
	QMap<int,QString> _rej_str_map;
	QMap<StrobType,QString> _strob_str_map;

	bool detpar_changing;
	bool rej_changing;
	bool npow_changing;
	bool vpow_changing;

	bool rez_strob;

	bool		us_copied;
	par_us_t	us_par_copied;
	par_osc_t	osc_par_copied;
	cn_info_t   cn_info_copied;
	public:
	Ui::ParamEditToolBar ui;
};

#endif // PARAMEDITTOOLBOX_H
