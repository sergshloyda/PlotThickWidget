#include "oscplotterscene.h"
#include "griditem.h"
#include "strobitem.h"
#include "qapplication.h"
OscPlotterScene::OscPlotterScene(QObject *parent)
	: QGraphicsScene(parent)
{
	setBackgroundBrush(QColor("#FEEDCA"));
	_deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
}

OscPlotterScene::~OscPlotterScene()
{
foreach(QGraphicsItem* item, items())
       {
            removeItem(item);
            delete item;
       }
}
void OscPlotterScene::draw_grid(int width,int height,quint8 numChan)
{
	QRectF rect=sceneRect();
	foreach(QGraphicsItem* item, items())
       {
            removeItem(item);
            delete item;
       }
	//addLine(0,height/2,width,height/2,QPen(Qt::black));   // ��������� �������������� ����� ����� �����
	//addLine(width/2,0,width/2,height,QPen(Qt::black));   // ��������� ������������ ����� ����� �����
	_grid_item=new GridItem(numChan);
	addItem(_grid_item);
	
	
}

DeviceSettings* OscPlotterScene::getDeviceSettings()const
{
	return _deviceSettings;
}
void OscPlotterScene::refresh_osc(const QByteArray& osc_array)
{
		
	_grid_item->refresh_osc(osc_array);

}