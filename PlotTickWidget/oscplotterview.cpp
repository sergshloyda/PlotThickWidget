#include "oscplotterview.h"
#include "qapplication.h"
OscPlotterView::OscPlotterView(QWidget *parent)
	: QGraphicsView(parent)
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // �������� ��������� �� �����������
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // �������� ��������� �� ���������
    this->setAlignment(Qt::AlignCenter);                        // ������ �������� ����������� � ������
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // ����������� ���������� �� �������
	DeviceSettings *deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
	_curr_num_chan=deviceSettings->getDeviceStruct().view_par.nchan;
    /* ����� ������� ����������� ������� �������
     * */
    this->setMinimumHeight(100);
    this->setMinimumWidth(100);
 
	_osc_plotter_scene = new OscPlotterScene(this);   // �������������� ����� ��� ���������
    this->setScene(_osc_plotter_scene);          // ������������� ����� � ������
 
   
 
    _build_pic_timer = new QTimer(this);               // �������������� ������
    _build_pic_timer->setSingleShot(true);
    // ���������� ���� ��� ��������� � �������
    connect(_build_pic_timer, SIGNAL(timeout()), this, SLOT(build_pic_tick()));
    _build_pic_timer->start(50);   

}

OscPlotterView::~OscPlotterView()
{

}
 void OscPlotterView::resizeEvent(QResizeEvent *res_event)
 {
	 _build_pic_timer->start(2);
	 QGraphicsView::resizeEvent(res_event);
 }
 void OscPlotterView::build_pic_tick()
 {
	 int width = this->width();      // ���������� ������ ������ �������
    int height = this->height();    // ���������� ������ ������ �������
    _osc_plotter_scene->setSceneRect(0,0,width,height);
	_osc_plotter_scene->draw_grid(width,height,_curr_num_chan);
 }
 void OscPlotterView::set_num_chan(quint8 numChan)
 {
	 _curr_num_chan=numChan;
	 _build_pic_timer->start(5);
 }

 void OscPlotterView::collect_osc(const QByteArray& osc_array)
{
		_osc_plotter_scene->refresh_osc(osc_array);
}