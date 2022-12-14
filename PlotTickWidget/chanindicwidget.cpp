#include "chanindicwidget.h"
#include "qdebug.h"
#include "qevent.h"
#include "qapplication.h"
#include <QTimer>
ChanIndicWidget::ChanIndicWidget(QWidget *parent)
	: QWidget(parent),_bClicked(false), _chan_num(-1)
{
	ui.setupUi(this);
	qApp->installEventFilter(this);
	label_arr[0] = ui.chan_0;
	label_arr[1] = ui.chan_1;
	label_arr[2] = ui.chan_2;
	label_arr[3] = ui.chan_3;
	label_arr[4] = ui.chan_4;
	label_arr[5] = ui.chan_5;
	label_arr[6] = ui.chan_6;
	label_arr[7] = ui.chan_7;
	label_arr[8] = ui.chan_8;
	label_arr[9] = ui.chan_9;
	label_arr[10] = ui.chan_10;
	label_arr[11] = ui.chan_11;
	label_arr[12] = ui.chan_12;
	label_arr[13] = ui.chan_13;
	label_arr[14] = ui.chan_14;
	label_arr[15] = ui.chan_15;
	std::vector<bool> vec_state;
	for(quint8 i = 0; i < MaxCount; i++)
	{
		label_arr[i]->setProperty("chan_number",i);
		label_arr[i]->setStyleSheet("background-color: rgb(255, 255, 255);");
		vec_state.push_back(i%2==0);
			
	}
	SetChannelStates(vec_state);
}

ChanIndicWidget::~ChanIndicWidget()
{

}
void ChanIndicWidget::SetChannelStates( const std::vector<bool>& vec_state)
{
	if(vec_state.size()>MaxCount)
		return;

	int i=0;
	for(auto pos=vec_state.begin();pos!=vec_state.end();++pos,i++)
	{
		if(*pos)
			label_arr[i]->setStyleSheet("background-color: rgb(171, 213, 171);");
		else
			label_arr[i]->setStyleSheet("background-color: rgb(255, 255, 255);");
		label_arr[i]->setVisible(true);
	}
	for(int ii = vec_state.size(); ii < MaxCount; ii++)// в общем случае количество каналов в настройках может не соответствовать 
		label_arr[ii]->setVisible(false);//лишние не отображаем
}
void  ChanIndicWidget::eventMousePressTimer()
{
	if(_bClicked)
	{
			if(_chan_num>=0)
				emit ChannelLClicked(_chan_num);//LeftMouseButtonChanClicked(_chan_num);
	}
	else
	{
		if(_chan_num>=0)
			emit ChannelDblClicked(_chan_num);//DblClickOnChan(_chan_num);
	}
}
bool ChanIndicWidget::eventFilter(QObject* pObj,QEvent* pEvent)
{
	

	
	if(pEvent->type()==QEvent::MouseButtonPress)
	{
		if(qstrcmp(pObj->metaObject()->className(),"QLabel")==0)
		{
			_chan_num=pObj->property("chan_number").toInt();
			if(static_cast<QMouseEvent*>(pEvent)->button()==Qt::LeftButton)
			{
				 _bClicked = true;
				 QTimer::singleShot(qApp->doubleClickInterval(), this, SLOT(eventMousePressTimer()));//для фильтрации двойного нажатия мышки
		
				
			}
			else if(static_cast<QMouseEvent*>(pEvent)->button()==Qt::RightButton)
			{
				if(_chan_num>0) 
					emit  ChannelRClicked(_chan_num);
					//RightMouseButtonChanClicked(_chan_num);
			}
		}
	}
	else if(pEvent->type()==QEvent::MouseButtonDblClick)
	{
		if(qstrcmp(pObj->metaObject()->className(),"QLabel")==0)
		{
			
			_chan_num=pObj->property("chan_number").toInt();
			_bClicked=false;
	
		}
	}
	

	return QObject::eventFilter(pObj,pEvent);
}