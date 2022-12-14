#ifndef OSCPLOTTERSCENE_H
#define OSCPLOTTERSCENE_H

#include <QGraphicsScene>
#include "devicesettings.h"
class GridItem;
class StrobItem;
class OscPlotterScene : public QGraphicsScene
{
	Q_OBJECT

public:
	OscPlotterScene(QObject *parent=0);
	~OscPlotterScene();
	void draw_grid(int width,int height,quint8 numChan);
	DeviceSettings* getDeviceSettings()const;
	void refresh_osc(const QByteArray& osc_array);

private:
	
	GridItem* _grid_item;
	StrobItem* _strob_item;
	DeviceSettings* _deviceSettings;
};

#endif // OSCPLOTTERSCENE_H
