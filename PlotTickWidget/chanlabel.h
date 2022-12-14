#ifndef CHANLABEL_H
#define CHANLABEL_H

#include <QLabel>
#include<qpainter.h>
#include <QPaintEvent>
#include <map>
#include "plotrowwidget.h"
#include"devicesettings.h"
class ChanLabel : public QLabel
{
	Q_OBJECT

public:
	ChanLabel(QWidget *parent);
	~ChanLabel();
	bool drawFrame;
	void setParent_(PlotRowWidget* plot_row_widget);

 PlotRowWidget* getParent_()
 {
	 return _parent;
 }
protected:
	void paintEvent(QPaintEvent * paint_event);	
	void mousePressEvent ( QMouseEvent * event );
signals:
	void clicked(quint8 numChan);
private:
 	PlotRowWidget* _parent;
	static const int  _txtMargin=9;
	DeviceSettings* _deviceSettings;
};

#endif // CHANLABEL_H
