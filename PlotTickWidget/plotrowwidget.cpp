#include "plotrowwidget.h"
#include "qpainter.h"
#include <QPaintEvent>
#include"chanlabel.h"
PlotRowWidget::PlotRowWidget(QWidget *parent,DrawStrategy* draw_strategy)
	: QWidget(parent),_draw_strategy(draw_strategy)
{

}
PlotRowWidget::PlotRowWidget(QWidget* parent,quint8 numChan):QWidget(parent),_numChan(numChan)
{
	DeviceSettings* _deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
	switch(_deviceSettings->getChanMode(numChan))
		{
		case TD_TOL:
			_draw_strategy=new DrawThickRow(numChan,_deviceSettings);
			break;
		case TD_TOL_LAM:
			_draw_strategy=new DrawThickLamRow(numChan,_deviceSettings);
			break;
		case TD_DEF_PROD:
		case TD_DEF_POPER:
			_draw_strategy=new DrawDefectRow(numChan,_deviceSettings);
			break;
		case TD_B_SCAN:
			_draw_strategy=new DrawBScanRow(_deviceSettings);
		}
}
PlotRowWidget::~PlotRowWidget()
{
	delete _draw_strategy;
}
void PlotRowWidget::paintEvent(QPaintEvent * paint_event)
{
 
QPainter painter(this);

	QRect cr=paint_event->rect();
	
	//painter.drawRect(cr.adjusted(1,1,-1,-1));
	cr.adjust(2,2,-1,-1);

	painter.fillRect(cr,Qt::white);
	painter.drawRect(cr);
	if (m_pixmap.isNull()) {
        painter.setPen(Qt::red);
        painter.drawText(rect(), Qt::AlignCenter, tr("Rendering channel row image, please wait..."));
        return;
    }
 
    painter.drawPixmap(0,0,m_pixmap);
}

void PlotRowWidget::setBuddy_(ChanLabel* buddy,QWidget* mainWindow)
{
		_buddy=buddy;
		_buddy->setParent_(this);
		connect(this,SIGNAL(clicked(quint8)),mainWindow,SLOT(select_channel(quint8)));
		connect(_buddy,SIGNAL(clicked(quint8)),mainWindow,SLOT(select_channel(quint8)));
}

void PlotRowWidget::mousePressEvent ( QMouseEvent * event )
{
	 switch (event->button()) {
        case Qt::LeftButton:
        {
            emit clicked(getNumChan());
            break;
        }
	}
  
}