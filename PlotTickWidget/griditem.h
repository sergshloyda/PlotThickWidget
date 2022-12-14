#ifndef GRIDITEM_H
#define GRIDITEM_H

#include <QGraphicsObject>
#include "oscplotterscene.h"
#include "qpainter.h"
#include "devicesettings.h"
#include "qpolygon.h"
class GridItem : public QGraphicsObject
{
	Q_OBJECT

public:
	GridItem(quint8 numChan,QGraphicsObject *parent=0);
	~GridItem();
	int type() const
	{
		return UserType + 2;
	}
void refresh_osc(const QByteArray& osc_array);
	
	

private:
	QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	quint8 _numChan;
	int _font_size;
	static const int grid_column_count=10;
	static const int grid_row_count=15;
	static const int x_margin=35;
	static const int y_margin=35;
	 QColor _gridColor;
	 QColor _textColor;
	 QColor _plot_color;
	DeviceSettings* _deviceSettings;
	float _x_b,_y_b;
	float _x_sign_step;
	float _y_sign_step;
	float log_5;
	float log_2;
	par_osc_t curr_osc_par;
	cn_info_t cn_info_par;
	view_cn_info_t curr_view_cn_par;
	QPolygonF _osc_line;  
};

#endif // GRIDITEM_H
