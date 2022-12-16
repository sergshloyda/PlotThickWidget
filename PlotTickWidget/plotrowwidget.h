#ifndef PLOTROWWIDGET_H
#define PLOTROWWIDGET_H

#include <QWidget>
#include "RenderThread.h"
#include "DrawDefectRow.h"
class ChanLabel;
class PlotRowWidget : public QWidget
{
Q_OBJECT

public:
	~PlotRowWidget();
	PlotRowWidget(QWidget *parent,DrawStrategy* draw_strategy);//obsolette
	PlotRowWidget(QWidget* parent,quint8 numChan);                       
	void Draw(const int w,const int h, const QList<Element_Info*>& elements_list)
	{
		setPixmap(QPixmap::fromImage(_draw_strategy->Draw(w,h,elements_list)));
	}

	void DrawPixmap(const QList<Element_Info*>& elements_list)
	{
		setPixmap(_draw_strategy->DrawPixmap(contentsRect().width(),contentsRect().height(),elements_list));
		update();
	}
	quint8 getNumChan(){return _numChan;}
	void setBuddy_(ChanLabel* buddy,QWidget* mainWindow);
	ChanLabel* getBuddy_(){return _buddy;}
signals:
	void clicked(quint8 numChan);
protected:
	void paintEvent(QPaintEvent * paint_event);
	void mousePressEvent ( QMouseEvent * event );
	PlotRowWidget(QWidget *parent){};
private:
	void setPixmap(const QPixmap& pixmap)
	{
		m_pixmap=pixmap;
		update();
	}
	QPixmap m_pixmap;
	quint8 _numChan;
	DrawStrategy* _draw_strategy;
	ChanLabel* _buddy;
};

#endif // PLOTROWWIDGET_H
