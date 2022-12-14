#ifndef PLOTMNEMOWIDGET_H
#define PLOTMNEMOWIDGET_H

#include <QWidget>
#include "RenderThread.h"
class PlotWidget : public QWidget
{
Q_OBJECT

public:
	~PlotWidget();
	PlotWidget(QWidget *parent,DrawStrategy* draw_strategy):QWidget(parent),_draw_strategy(draw_strategy){
		}

	void DrawPixmap(const QList<Element_Info*>& elements_list)
	{
		setPixmap(_draw_strategy->DrawPixmap(contentsRect().width(),contentsRect().height(),elements_list));
	}
protected:
	void paintEvent(QPaintEvent * paint_event);
	PlotWidget(QWidget *parent);
private:
	void setPixmap(const QPixmap& pixmap)
	{
		m_pixmap=pixmap;
		update();
	}
	QPixmap m_pixmap;

	DrawStrategy* _draw_strategy;
	
};

#endif // PLOTMNEMOWIDGET_H
