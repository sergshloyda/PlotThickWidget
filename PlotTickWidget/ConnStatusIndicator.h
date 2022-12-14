#pragma once
#include "ui_ParamEditToolBar.h"
#include "paramedittoolbox.h"
#define NUM_INTERFACE_MODES		2
struct ConnectionStatusWidgets
{
	quint8 conn_state;
	QLabel *label_noConn;
};
class ConnStatusIndicator
{
public:
	ConnStatusIndicator(bool setup_mode);
	~ConnStatusIndicator(void);
	enum ConnectionState{
		Connection_OFF=0,
		Connection_ON=1,
		Connection_ERROR=2
	};
	///void InitUi(Ui::ParamEditToolBar *ui_set);
	//void InitUi(Ui::q_win_sepia_view *ui_view);

	void InitFromWidget(ParamEditToolBox* tool_box_setup);

	void SwitchToSetupMode();
	void SwitchToViewMode();


	ConnectionStatusWidgets *ConnWidgets();

	void SetConnState(const quint8 state, const QString &error_text = QString());		// 0 - выкл, 1 - соединено, 2 - ошибка
private:
	ConnectionStatusWidgets stat_widgets[NUM_INTERFACE_MODES];
	bool _setup_mode;
};

