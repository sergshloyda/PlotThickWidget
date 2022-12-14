#include "chanlabel.h"
#include "plotrowwidget.h"
#include"qfontmetrics.h"
ChanLabel::ChanLabel(QWidget *parent)
	: QLabel(parent),drawFrame(false)
{
	setText("ChanLabel");
	_deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
	/*QPainter painter(this);*/
	QFontMetrics fm = qApp->fontMetrics();
	int width = fm.width("00-TD_DEF_POPER");
	setFixedWidth(width+_txtMargin*2);
	
	_parent=0;
}

ChanLabel::~ChanLabel()
{

}
void ChanLabel::paintEvent(QPaintEvent * paint_event)
{
 

QPainter painter(this);
	QRect cr=paint_event->rect();
	painter.drawRect(cr.adjusted(1,1,-1,-1));
	cr.adjust(2,2,-1,-1);
	painter.fillRect(cr,Qt::white);
	painter.setPen(_deviceSettings->getOscColor("TEXT_COLOR"));
	painter.drawText(rect(), Qt::AlignCenter, text());
	if(drawFrame)
	{
		QPen pen(_deviceSettings->getOscColor("SEL_CHAN_FRAME_COLOR"));
		pen.setWidth(3);
		pen.setStyle(Qt::DashLine);
		painter.setPen(pen);
		painter.drawRect(rect().adjusted(5,5,-5,-5));
	}
       
 
}

void ChanLabel::mousePressEvent(QMouseEvent *event)
{
	if(!_parent) return;
    switch (event->button()) {
        case Qt::LeftButton:
        {
			emit clicked(_parent->getNumChan());
            break;
        }
	}
  
    repaint();
}
void ChanLabel::setParent_(PlotRowWidget* plot_row_widget)
	{
		_parent=plot_row_widget;

		setText(tr("%1-%2").arg(_parent->getNumChan()+1).arg(_deviceSettings->getChanModeName(_parent->getNumChan())));
	}