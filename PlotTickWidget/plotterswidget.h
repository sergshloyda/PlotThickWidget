#ifndef PLOTTERSWIDGET_H
#define PLOTTERSWIDGET_H

#include <QWidget>
#include <QPainter.h>
#include <QPaintEvent>
#include "devicesettings.h"
class PlottersWidget : public QWidget
{
	Q_OBJECT

public:
	PlottersWidget(QWidget *parent);
	~PlottersWidget();
protected:
	void paintEvent(QPaintEvent *);

private:
	void PlotThick(QPainter & painter, const QRect& content_rect,const quint8 nChan);
	void PlotDefect(QPainter & painter, const QRect& content_rect,const quint8 chan);
	void PlotThickLam(QPainter & painter, const QRect& content_rect,const quint8 chan);
private:
	DeviceSettings* _deviceSettings;
	static const int MaxAmpl=255;
};

#endif // PLOTTERSWIDGET_H
