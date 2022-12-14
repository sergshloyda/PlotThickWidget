#include "plotmnemowidget.h"
#include "qpainter.h"
#include <QPaintEvent>
PlotWidget::PlotWidget(QWidget *parent)
	: QWidget(parent)
{

}

PlotWidget::~PlotWidget()
{
	delete _draw_strategy;
}
void PlotWidget::paintEvent(QPaintEvent * paint_event)
{
 
QPainter painter(this);

	QRect cr=paint_event->rect();
	
	painter.drawRect(cr.adjusted(1,1,-1,-1));
	cr.adjust(2,2,-1,-1);
	painter.fillRect(cr,Qt::white);
	if (m_pixmap.isNull()) {
        painter.setPen(Qt::red);
        painter.drawText(rect(), Qt::AlignCenter, tr("Rendering  image, please wait..."));
        return;
    }
 
    painter.drawPixmap(0,0,m_pixmap);
}