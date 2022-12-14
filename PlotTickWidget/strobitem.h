#ifndef STROBITEM_H
#define STROBITEM_H

#include <QGraphicsObject>

class StrobItem : public QGraphicsObject
{
	Q_OBJECT

public:
	StrobItem(QGraphicsObject *parent=0);
	~StrobItem();
		int type() const
	{
		return UserType + 3;
	}
protected:
	QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
	
};

#endif // STROBITEM_H
