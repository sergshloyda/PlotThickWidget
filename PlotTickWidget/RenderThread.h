#ifndef __RENDER_THREAD_H__
#define __RENDER_THREAD_H__

#include"element_info.h"
#include "ThickElement.h"
#include "devicesettings.h"
#include "qapplication.h"
class DrawStrategy
{
public:
	virtual ~ DrawStrategy(){}
	DrawStrategy(DeviceSettings* device_settings):_deviceSettings(device_settings){
	//_deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
	}
	virtual QImage Draw(int w,int h, const QList<Element_Info*>& list)=0;
	virtual QPixmap DrawPixmap(int w,int h, const QList<Element_Info*>& list)=0;
protected:
	
	DeviceSettings* _deviceSettings;
	
};
class DrawDefectRow:public DrawStrategy
{
public:
	DrawDefectRow(quint8 num_chan,DeviceSettings* device_settings):DrawStrategy(device_settings),
	  _num_chan(num_chan),_beg_index(1) {}
		
	virtual QImage Draw(int w,int h,const QList<Element_Info*>& list)override;
	virtual QPixmap DrawPixmap(int w,int h, const QList<Element_Info*>& list)override;
private:
	quint8 _num_chan;
	int _beg_index;
};
class DrawThickRow:public DrawStrategy
{
public:
	DrawThickRow(quint8 num_chan,DeviceSettings* device_settings):DrawStrategy(device_settings),
	  _num_chan(num_chan) {}

	virtual QImage Draw(int w,int h,const QList<Element_Info*>& list)override;
	virtual QPixmap DrawPixmap(int w,int h, const QList<Element_Info*>& list)override;
private:
	quint8 _num_chan;
	
};
class DrawThickLamRow:public DrawStrategy
{
public:
	DrawThickLamRow(quint8 num_chan,DeviceSettings* device_settings):DrawStrategy(device_settings),
	  _num_chan(num_chan) {}
	virtual QImage Draw(int w,int h,const QList<Element_Info*>& list)override;
	virtual QPixmap DrawPixmap(int w,int h, const QList<Element_Info*>& list)override;
private:
	quint8 _num_chan;
};
class DrawMnemoRow:public DrawStrategy
	{
public:
	DrawMnemoRow(DeviceSettings* device_settings);
	virtual QImage Draw(int w,int h,const QList<Element_Info*>& list)override;
	virtual QPixmap DrawPixmap(int w,int h, const QList<Element_Info*>& list)override;
	private:
		QColor _mnemo_background_color;
		QColor _error_color;
		QColor _thick_color;
		QColor _sufficient_condition_color;
		QColor _sep_line_color;
		QColor _flaw_poper_color,_flaw_prod_color;
		QColor _osc_background_color;
		int _beg_index;
};
class DrawCoordRow:public DrawStrategy
	{
public:
	DrawCoordRow(DeviceSettings* device_settings);
	virtual QImage Draw(int w,int h,const QList<Element_Info*>& list)override;
	virtual QPixmap DrawPixmap(int w,int h, const QList<Element_Info*>& list)override;
	private:
		static const int txtWidth = 30;
	
};
class DrawBScanRow:public DrawStrategy
	{
public:
	DrawBScanRow(DeviceSettings* device_settings):DrawStrategy(device_settings){}
	virtual QImage Draw(int w,int h,const QList<Element_Info*>& list)override;
	virtual QPixmap DrawPixmap(int w,int h, const QList<Element_Info*>& list)override;
	private:
	
	
};

class RenderThread : public QObject {
 Q_OBJECT
 public:
	 RenderThread(DrawStrategy* draw_strategy):_draw_strategy(draw_strategy){}
	 virtual ~RenderThread(){delete _draw_strategy;}
 public slots:
     void rendering(int w,int h, QList<Element_Info*> list);
	
 signals:
     void finished();
     void error(QString err);
	 void onDraw(const QImage& img);
private:
	int _w;
	int _h;
	int _cnt;
	DrawStrategy* _draw_strategy;
};
#endif