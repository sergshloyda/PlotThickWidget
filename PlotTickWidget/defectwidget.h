#ifndef DEFECTWIDGET_H
#define DEFECTWIDGET_H

#include <QWidget>
#include <QPainter.h>
#include <QPaintEvent>
#include "devicesettings.h"
class DefectWidget : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(quint8 num_chan READ getNumChan WRITE setNumChan)
public:
	DefectWidget(QWidget *parent);
	~DefectWidget();
	void setNumChan(const quint8 nChan);
	quint8 getNumChan() const;
protected:
	void paintEvent(QPaintEvent *);
private:
	void PlotDefect(QPainter & painter, const QRect& content_rect,const quint8 chan);
	DeviceSettings* _deviceSettings;
	static const int MaxAmpl=255;
	quint8 _nChan;
};

#endif // DEFECTWIDGET_H
