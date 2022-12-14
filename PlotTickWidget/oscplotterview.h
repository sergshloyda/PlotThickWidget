#ifndef OSCPLOTTERVIEW_H
#define OSCPLOTTERVIEW_H

#include <QGraphicsView>
#include "qtimer.h"
#include "oscplotterscene.h"
class OscPlotterView : public QGraphicsView
{
	Q_OBJECT
	Q_PROPERTY(quint8 NumChan READ get_num_chan WRITE set_num_chan)

public:
	OscPlotterView(QWidget *parent=0);
	~OscPlotterView();
	quint8 get_num_chan(){return _curr_num_chan;}
	void set_num_chan(quint8 numChan);
protected:
	 void resizeEvent(QResizeEvent *res_event);

private slots:
	void build_pic_tick();
	void collect_osc(const QByteArray& osc_array);
private:
	QTimer* _build_pic_timer;
	OscPlotterScene* _osc_plotter_scene;
	quint8 _curr_num_chan;
};

#endif // OSCPLOTTERVIEW_H
