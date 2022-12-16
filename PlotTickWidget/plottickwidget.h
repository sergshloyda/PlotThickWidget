#ifndef PLOTTICKWIDGET_H
#define PLOTTICKWIDGET_H

#include <QtWidgets/QMainWindow>
#include "ui_plottickwidget.h"
#include "qtimer.h"
#include "dev_struct.h"
#include "element_info.h"
#include "ElementFactory.h"
#include "devicesettings.h"
#include "devicecmdobject.h"
//#include "plotterswidget.h"
//#include "thicklaminwidget.h"
//#include "defectwidget.h"
//#include "thickwidget.h"
#include "plotrowwidget.h"
#include "plotmnemowidget.h"
#include "devicedata.h"
#include "chanlabel.h"
#include "oscplotterscene.h"
#include "OscillogramPlotterSetter.h"
#include "OscillogramProperties.h"
#include "OscillogramWidget.h"
#include "paramedittoolbox.h"
#include "ui_ParamEditToolBar.h"
#include "ConnStatusIndicator.h"
#include "par_object_local.h"
#include "dialloadsavepar.h"
#include "dialpar.h"

#define NUM_RESULT_STRBS		5


Q_DECLARE_METATYPE(QList<Element_Info*>);
Q_DECLARE_METATYPE(QList<int>);
class PlotTickWidget : public QWidget
{
	Q_OBJECT

public:
	PlotTickWidget(QWidget *parent = 0);
	~PlotTickWidget();
	enum MainWindowMode
	{
		SetupMode=0,
		ViewMode=1
	};
protected:
//	void paintEvent(QPaintEvent *);
	/*QSize minimumSize() const;
	QSize sizeHint() const;*/
	void closeEvent(QCloseEvent *event);
protected slots:
	void received_data();
	void redraw();
	void on_pushButton_clicked();
	void on_writeBtn_clicked();
	void on_readBtn_clicked();
	void on_add_vrch_point_clicked();
	void select_channel(quint8 numChan);
	void chan_us_set_toggled(quint8 numChan);
	void dev_param_edit();
	void reset_buffers();
	void ExitWithSave();
public slots:
	void NoConnection();
	void slot_unsuccesfull();
	void slot_succesfull();
	void WrongDeviceMode();
	void EndInitConnection();
	void draw_osc();
	void draw_spectr();
	void collect_amps(QByteArray data);

	void StartStopAction();
	void SwitchToSetupMode();
	void SwitchToViewMode();
	void butt_save_par();
	void butt_load_par();
	void save_par_in_dev();
	void load_par_from_dev();
	void regenerate_auto_par_set();
	void change_directories();
	void setup_params();
	void show_mab_setup();
	void show_channel_setup();
	void show_algor_setup();
	void show_selection_setup();
	void changeColors();

signals:
	void collect_osc(const QByteArray& osc_array);
	void exiting();
private:

	Ui::PlotTickWidgetClass ui;

	QTimer* timer;
	QTimer* redraw_timer;
	
	QList<Element_Info*> _elem_list;
	FactoryContainer* _factoryContainer;
	DeviceCmdObject* _dev_cmd;
	DeviceSettings* _deviceSettings;

	quint8 old_nparam;
	bool result_file_param_loaded;


	DialLoadSavePar *dial_ld_save;
	DialPar* _dial_par;
	
	QString filePath;

	QString ParamDirName;
	QString LibraryDirName;
	QString ResultDirName;


	static const int qty_channels=14;
	static const int MaxAmpl=255;

	QVector<PlotRowWidget*> _row_widgets;
	QVector<ChanLabel*> _row_chan_labels;
	PlotWidget* _mnemo_widget;
	PlotWidget* _coord_widget;
	ParamEditToolBox* _param_edit_tool_box;
	OscillogramWidget* _osc_widget;
	QVBoxLayout *_widgets_layout;
	QGridLayout * _gridLayout;
	ChanLabel* _coord_label;
	ChanLabel* _mnemo_label; 
	DeviceData dev_data;
	
	float sub_thick;
	amp_us_struct_t us_time;
	OscillogramProperties OscProperties;
	//OscillogramPlotterSetter* OscPlotter;
	//bool ed_enabled;
	bool _setup_mode;
	MainWindowMode _main_window_mode;
	quint8 tube_mode;

	par_setting_local _local_settings;
	par_setting_local _loaded_settings;		// _loaded_settings относится только к загруженному из файла настроек
	par_object_local local_object;

	ConnStatusIndicator _conn_stat_ind;
public:
	bool get_ed_enabled() const;
	void set_ed_enabled(const bool ed_enabled);
	void show_gens_info(const QString& txt_info);
	void show_ampl_info(const QString& txt_info);
	void update_chan_rows();
	void update_osc_widget();
	void apply_chan_selection(const quint8 num_chan,const bool replot);
	void reset_row_widgets();
private:
	void saveSettings();
	void loadSettings();
	void check_param_saving();	
	bool load_params(bool startup, bool load_strings = true);
	bool save_params();
	void apply_main_window_title(MainWindowMode window_mode);
	void setup_connections();
	
};

#endif // PLOTTICKWIDGET_H
