#include "oscplotterview.h"
#include "qapplication.h"
OscPlotterView::OscPlotterView(QWidget *parent)
	: QGraphicsView(parent)
{
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету
	DeviceSettings *deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
	_curr_num_chan=deviceSettings->getDeviceStruct().view_par.nchan;
    /* Также зададим минимальные размеры виджета
     * */
    this->setMinimumHeight(100);
    this->setMinimumWidth(100);
 
	_osc_plotter_scene = new OscPlotterScene(this);   // Инициализируем сцену для отрисовки
    this->setScene(_osc_plotter_scene);          // Устанавливаем сцену в виджет
 
   
 
    _build_pic_timer = new QTimer(this);               // Инициализируем Таймер
    _build_pic_timer->setSingleShot(true);
    // Подключаем СЛОТ для отрисовки к таймеру
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
	 int width = this->width();      // определяем ширину нашего виджета
    int height = this->height();    // определяем высоту нашего виджета
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