#include "strobitem.h"
#include "qpainter.h"
StrobItem::StrobItem(QGraphicsObject *parent)
	: QGraphicsObject(parent)
{

}

StrobItem::~StrobItem()
{

}
QRectF StrobItem::boundingRect() const
{
	return QRectF(0,0,50,5);
	//	return _parent_scene->sceneRect();
}
void StrobItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->drawEllipse(boundingRect());
}