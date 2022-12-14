#include "ConnStatusIndicator.h"


ConnStatusIndicator::ConnStatusIndicator(bool setup_mode): _setup_mode(setup_mode)
{
}


ConnStatusIndicator::~ConnStatusIndicator(void)
{
}
//void ConnStatusIndicator::InitUi(Ui::ParamEditToolBar *ui_set)
//{
//	// 0 - режим настройки
//	// 1 - режим просмотра/контроля
//
//	ConnectionStatusWidgets &curr_widgets = stat_widgets[0];
//
//	curr_widgets.conn_state = 0;
//	curr_widgets.label_noConn = ui_set->label_noConn;
//}
void ConnStatusIndicator::InitFromWidget(ParamEditToolBox* tool_box_setup)
{
	//ConnectionStatusWidgets &curr_widgets = stat_widgets[0];
	stat_widgets[0].conn_state=0;
	stat_widgets[0].label_noConn=tool_box_setup->getLabelConn();
}
void ConnStatusIndicator::SwitchToViewMode()
{
	stat_widgets[1].conn_state = stat_widgets[0].conn_state;
	stat_widgets[1].label_noConn->setStyleSheet( stat_widgets[0].label_noConn->styleSheet()) ;
	stat_widgets[1].label_noConn->setText( stat_widgets[0].label_noConn->text() );
}


void ConnStatusIndicator::SwitchToSetupMode()
{
	stat_widgets[0].conn_state = stat_widgets[1].conn_state;
	stat_widgets[0].label_noConn->setStyleSheet( stat_widgets[1].label_noConn->styleSheet() );
	stat_widgets[0].label_noConn->setText( stat_widgets[1].label_noConn->text() );
}


void ConnStatusIndicator::SetConnState(const quint8 state, const QString &error_text)		// 0 - выкл, 1 - соединено, 2 - ошибка
{
	quint8 n = _setup_mode ? 0 : 1;

	if(stat_widgets[n].conn_state != state)
	{
		stat_widgets[n].conn_state = state;
		switch(state)
		{
		case Connection_ON:
			stat_widgets[n].label_noConn->setStyleSheet("background-color: rgb(0, 128, 0); color: rgb(255, 255, 255)");
			stat_widgets[n].label_noConn->setText(QString());
			break;

		case Connection_ERROR:
			stat_widgets[n].label_noConn->setStyleSheet("background-color: rgb(255, 50, 50); color: rgb(255, 255, 255)");
			break;

		case Connection_OFF:
		
			stat_widgets[n].label_noConn->setStyleSheet(QString());
			stat_widgets[n].label_noConn->setText(QString());
		}
	}

	if(state == Connection_ERROR)
		stat_widgets[n].label_noConn->setText(error_text);
}

ConnectionStatusWidgets *ConnStatusIndicator::ConnWidgets()
{
	if(_setup_mode)
		return stat_widgets;

	return stat_widgets + 1;
}