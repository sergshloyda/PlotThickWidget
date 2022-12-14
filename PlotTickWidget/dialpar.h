#ifndef DIALPAR_H
#define DIALPAR_H

#include <QDialog>
#include "ui_dial_par.h"
#include "params.h"
#include <vector>
#include"devicesettings.h"
#include "qbytearray.h"
#include <tuple>
#include "qevent.h"
class BadInputException:public std::exception
{
public:
explicit BadInputException(const char* message)
        : _msg(message) {}
    explicit BadInputException(const std::string& message)
        : _msg(message) {}
    virtual ~BadInputException()  {}
    virtual const char* what() const  {
       return _msg.c_str();
    }
protected:
    std::string _msg;
};

class DialPar : public QDialog
{
	Q_OBJECT

public:
	DialPar(QWidget *parent);
	~DialPar();

	void set_chans(const par_izm_t &izm_par, const cn_list_t& cn_list, const std::vector<quint8>& us_inputs);
	void get_chans(std::vector<std::tuple<quint8,quint8,quint8>>& chan_info,std::vector<quint8>& us_inputs);

	quint8 get_num_tacts();
	quint8 get_num_chans();
	quint8 get_number_per_element();

	void set_conn_settings(const QString &new_ip_addr);
	QString get_conn_settings() const;

	void  set_zond_freq(int freq);
	int  get_zond_freq() const;

	void set_filtr_par(const par_filtr_t &in_filtr_par);
	void get_filtr_par(par_filtr_t& out_filtr_par) ;

	void set_control_step(const quint8 in_control_step);
	quint8 get_control_step() const;

	void set_axis_modes(DeviceSettings* device_settings);

	void set_layer_flags(const quint8 flags);
	quint8 get_layer_flags() const;


	void set_manual_speed(const par_manual_speed_t &in_manual_speed);
	void get_manual_speed(par_manual_speed_t& out_manual_speed) ;

	void set_coef_coord(const quint16 in_coef_coord);
	quint16 get_coef_coord() const;

	void set_string_par(const par_info_strings_t &in_str_par);
	void get_string_par(par_info_strings_t *out_str_par);

	void set_vdp_param(const par_vdp_t &in_vdp);
	void get_vdp_param(par_vdp_t *out_vdp);

	void enable_params(const bool is_enable);

	bool modified() const;
protected:
	void showEvent(QShowEvent * _event) override;
protected slots:
	void VDP_changed();
	void ninp_changed(); 

	virtual void accept() override;

	void chan_count_changed();
	void tact_number_changed();

	void update_interval_changed();
	void time_interval_changed();



private:
	inline int index_for_us_rej(const quint8 rej);
	inline quint8 us_rej_of_index(const int index);
	inline quint8 get_us_from_input(const quint8 input) const;
	inline void show_enabled_chanals();

	void apply_chan_params();


private:
	Ui::Dialog_par ui;
	quint8 _chan_count;
	quint8 _old_num_chan;
	cn_info_t _local_cn_info[NUM_CHANS];

	quint8 _num_tacts;
	quint8 _old_num_tacts;

	quint8 _num_per_elem;

	par_filtr_t _filtr_par;

	par_manual_speed_t _manual_speed;

	quint16 _coef_coord;

	quint16 _temp_vdp_speed;

	std::vector<quint8> _us_inputs;


	QLabel *chan_label_arr[NUM_CHANS];
	ParamLineEdit *ed_tact_arr[NUM_CHANS];
	ParamLineEdit *ed_ninp_arr[NUM_CHANS];
	QComboBox *comb_rej_arr[NUM_CHANS];
	QByteArray chan_prop_name;

	bool was_modified;

};

#endif // DIALPAR_H
