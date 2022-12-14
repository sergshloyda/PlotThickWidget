#include "plotterswidget.h"
#include "dev_struct.h"
#include"qapplication.h"
#include "ThickElement.h"

PlottersWidget::PlottersWidget(QWidget *parent)
	: QWidget(parent)
{
	_deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
}

PlottersWidget::~PlottersWidget()
{

}
void PlottersWidget::paintEvent(QPaintEvent * paint_event)
{
	QPainter painter(this);

	QRect cr=paint_event->rect();
	painter.fillRect(cr,Qt::white);
	painter.drawRect(cr);
	QRect plotter_wdg_rect=cr;
	plotter_wdg_rect.setHeight(cr.height()/4);
	painter.drawRect(plotter_wdg_rect);
	painter.save();
	
	PlotThick(painter,plotter_wdg_rect,0);
	painter.restore();
	painter.save();
	painter.translate(0,cr.height()/4);
	painter.drawRect(plotter_wdg_rect);
	PlotDefect(painter,plotter_wdg_rect,1);
	painter.restore();
	painter.save();
	painter.translate(0,cr.height()/2);
	painter.drawRect(plotter_wdg_rect);
	
	PlotThickLam(painter,plotter_wdg_rect,2);
	painter.restore();
	painter.save();
	painter.translate(0,(cr.height()*3)/4);
	painter.drawRect(plotter_wdg_rect);
	PlotDefect(painter,plotter_wdg_rect,3);
	painter.restore();
}
void PlottersWidget::PlotThick(QPainter & painter, const QRect& content_rect,const quint8 nChan)
{
	if((_deviceSettings->getChanMode(nChan)!=TD_TOL) && (_deviceSettings->getChanMode(nChan)!=TD_TOL_LAM))return;
	float norm_val = 10.0;

	const Qt::FillRule fill_rule=Qt::WindingFill;





	float por_pos = 0;
	float por_neg = 0;

	float curr_range;

	float min_val = 8.0;
	float max_val = 12.0;

	float thick_range_koef=0.2;
	float pixmap_height=content_rect.height();
	float pixmap_width=content_rect.width();
	float left_tab=content_rect.left();



	curr_range = max_val * (1 + thick_range_koef);

	por_neg = 0;
	por_pos = curr_range;





	const float plot_step_thick_y = (pixmap_height - 1) / curr_range;
	const float porog_max = (max_val - por_neg) * plot_step_thick_y;
	painter.save();
	painter.translate(left_tab,0);
	QPen pen2;
	pen2.setColor(Qt::darkGray);
	painter.setPen(pen2);
	QLineF dash_line( /*left_tab*/0,  porog_max, pixmap_width,  porog_max);
	painter.drawLine(dash_line);


	const float porog_min = (min_val - por_neg) * plot_step_thick_y;

	pen2.setColor(Qt::red);
	painter.setPen(pen2);
	dash_line.setLine( /*left_tab +*/ 2,  porog_min, pixmap_width,  porog_min);
	painter.drawLine(dash_line);


	const float porog_opt = (norm_val - por_neg) * plot_step_thick_y;

	pen2.setColor(Qt::darkGreen);
	painter.setPen(pen2);
	dash_line.setLine(/* left_tab + */1,  porog_opt, pixmap_width,  porog_opt);
	painter.drawLine(dash_line);	

	painter.resetTransform();
	painter.restore();





	QPolygonF poligon_min;
	bool poligon_min_started = false;
	bool poligon_min_lower = false;


	QPolygonF poligon_max;
	bool poligon_max_started = false;
	bool poligon_max_upper = false;

	float plot_step_x=3.0;



	float curr_x = left_tab - plot_step_x;
	float max_y = pixmap_height - 1;

	//	float curr_x_middle = left_tab + plot_step_x/2;



	int curr_area_count = -1;			// -1 - не заполнялась, 0 - под графиком, 1 - ниже нижн. порога, 2 - в норме, 3 - выше верхн. порога, 4 - над графиком
	int prev_area_count = curr_area_count;


	int curr_max_area_n = -1;
	int prev_max_area_n = curr_max_area_n;



	float prev_thickness = 0.0f;
	float prev_max_thickness = 0.0f;
	bool prev_max_in_possible = false;



	QLineF line;
	QPen pen1;
	pen1.setColor(Qt::darkMagenta);

	QPen pen_2(pen1);
	QPen pen3(pen1);

	pen_2.setColor(Qt::red);
	pen3.setColor(Qt::darkGreen);

	QPen pen4(pen1);
	pen4.setColor(Qt::darkGreen);
	QVector<qreal> dash_paretten;
	dash_paretten << 1 << 1;
	pen4.setDashPattern(dash_paretten);


	QBrush brush1(Qt::darkMagenta, Qt::SolidPattern);
	QBrush brush2(Qt::red, Qt::SolidPattern);



	float base_x_pos;
	float base_x_pos_lim;
	float base_x_neg_lim;
	float base_x_neg;

	int requested_size=pixmap_width/plot_step_x+1;
	int beg=0;
	/*if(requested_size<data_list.count())
	{
	beg=data_list.count()-requested_size;
	}*/
QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
	if(requested_size<elem_list.count())
	{
		beg=elem_list.count()-requested_size;
	}
	//for(int j = beg; j < data_list.count(); j++)
	for(int j = beg; j < elem_list.count(); j++)
	{
		bool thick_filled = false;

		//thick_info_t *p_thick_info=data_list[j].value<thick_info_t *>();
		ThickElement* thick_elem;
		
		
				thick_elem=static_cast<ThickElement*>(elem_list[j]->chan_info_array[nChan]);
		
		


		/*	if(p_thick_info->filled)
		{
		if(p_thick_info->thick.min_thick <= p_thick_info->thick.max_thick)
		thick_filled = true;
		}*/

		if(thick_elem->filled)
		{
			if(thick_elem->thick.min_thick <= thick_elem->thick.max_thick)
				thick_filled = true;
		}

		if(thick_filled)
		{
			//float curr_thick = p_thick_info->thick.min_thick;
			float curr_thick = thick_elem->thick.min_thick;
			if( curr_thick <=  por_neg)
			{

			}
			else if( curr_thick <  min_val)
			{
				curr_area_count = 1;

				switch(prev_area_count)
				{
				case -1:

					painter.setPen(pen_2);
					painter.setBrush(brush2);

					poligon_min << QPointF(curr_x + plot_step_x, porog_min) << QPointF(curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					poligon_min_started = true;
					break;


				case 0:

					base_x_neg = curr_x + plot_step_x * ( prev_thickness - por_neg )/( prev_thickness - curr_thick );

					poligon_min << QPointF(base_x_neg,  0) << QPointF(curr_x + plot_step_x,  ((curr_thick - por_neg) * plot_step_thick_y) );
					poligon_min_lower = false;
					break;

				case 1:

					poligon_min << QPointF( curr_x + plot_step_x,  ((curr_thick - por_neg) * plot_step_thick_y) );
					break;


				case 2:

					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );

					line.setLine( curr_x,  ((prev_thickness - por_neg) * plot_step_thick_y), base_x_neg_lim,  porog_min);
					painter.drawLine(line);

					painter.setPen(pen_2);
					painter.setBrush(brush2);

					poligon_min << QPointF(base_x_neg_lim,  porog_min) << QPointF(curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					poligon_min_started = true;

					break;

				case 3:

					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );
					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );

					/*					poligon_max << QPointF(base_x_pos_lim,  porog_max);
					painter.drawPolygon(poligon_max,fill_rule);
					poligon_max.clear();
					poligon_max_started = false;*/

					line.setLine( curr_x,  ((prev_thickness - por_neg) * plot_step_thick_y), base_x_pos_lim,  porog_max);
					painter.drawLine(line);


					painter.setPen(pen3);

					line.setLine( base_x_pos_lim,  porog_max, base_x_neg_lim,  porog_min);
					painter.drawLine(line);

					painter.setPen(pen_2);
					painter.setBrush(brush2);

					poligon_min << QPointF(base_x_neg_lim,  porog_min) << QPointF(curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					poligon_min_started = true;

					break;


				case 4:

					base_x_pos = curr_x + plot_step_x * ( prev_thickness - por_pos )/( prev_thickness - curr_thick );

					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );
					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );


					line.setLine( curr_x,  max_y, base_x_pos,  max_y);
					painter.drawLine(line);

					line.setLine( base_x_pos,  max_y, base_x_pos_lim,  porog_max);
					painter.drawLine(line);

					/*					poligon_max << QPointF(base_x_pos,  max_y) << QPointF(base_x_pos_lim, porog_max);
					painter.drawPolygon(poligon_max,fill_rule);
					poligon_max.clear();
					poligon_max_started = false;
					poligon_max_upper = false;*/


					painter.setPen(pen3);

					line.setLine( base_x_pos_lim,  porog_max, base_x_neg_lim,  porog_min);
					painter.drawLine(line);

					painter.setPen(pen_2);
					painter.setBrush(brush2);

					poligon_min << QPointF(base_x_neg_lim,  porog_min) << QPointF(curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					poligon_min_started = true;

					break;


				default:;
				}

			}
			else if( curr_thick <=  max_val)
			{
				curr_area_count = 2;

				switch(prev_area_count)
				{
				case -1:

					painter.setPen(pen3);
					break;


				case 0:

					base_x_neg = curr_x + plot_step_x * ( prev_thickness - por_neg )/( prev_thickness - curr_thick );
					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );


					poligon_min << QPointF(base_x_neg,  0) << QPointF(base_x_neg_lim,  porog_min);
					painter.drawPolygon(poligon_min,fill_rule);
					poligon_min.clear();
					poligon_min_started = false;
					poligon_min_lower = false;


					painter.setPen(pen3);

					line.setLine( base_x_neg_lim,  porog_min, curr_x + plot_step_x,  ((curr_thick - por_neg) * plot_step_thick_y));
					painter.drawLine(line);
					break;

				case 1:

					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );

					poligon_min << QPointF(base_x_neg_lim,  porog_min);
					painter.drawPolygon(poligon_min,fill_rule);
					poligon_min.clear();
					poligon_min_started = false;


					painter.setPen(pen3);

					line.setLine( base_x_neg_lim,  porog_min, curr_x + plot_step_x,  ((curr_thick - por_neg) * plot_step_thick_y));
					painter.drawLine(line);
					break;


				case 2:

					line.setLine( curr_x,  ((prev_thickness - por_neg) * plot_step_thick_y), curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y) );
					painter.drawLine(line);
					break;

				case 3:

					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );

					/*					poligon_max << QPointF(base_x_pos_lim,  porog_max);
					painter.drawPolygon(poligon_max,fill_rule);
					poligon_max.clear();
					poligon_max_started = false;*/

					line.setLine( curr_x,  ((prev_thickness - por_neg) * plot_step_thick_y), base_x_pos_lim,  porog_max);
					painter.drawLine(line);



					painter.setPen(pen3);

					line.setLine( base_x_pos_lim,  porog_max, curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					painter.drawLine(line);
					break;

				case 4:

					base_x_pos = curr_x + plot_step_x * ( prev_thickness - por_pos )/( prev_thickness - curr_thick );
					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );

					/*					poligon_max << QPointF(base_x_pos,  max_y) << QPointF(base_x_pos_lim, porog_max);
					painter.drawPolygon(poligon_max,fill_rule);
					poligon_max.clear();
					poligon_max_started = false;
					poligon_max_upper = false;*/


					line.setLine( curr_x,  max_y, base_x_pos,  max_y);
					painter.drawLine(line);

					line.setLine( base_x_pos,  max_y, base_x_pos_lim,  porog_max);
					painter.drawLine(line);


					painter.setPen(pen3);

					line.setLine( base_x_pos_lim,  porog_max, curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					painter.drawLine(line);

					break;

				default:;
				}
			}
			else if( curr_thick <  por_pos)
			{
				curr_area_count = 3;

				switch(prev_area_count)
				{
				case -1:

					painter.setPen(pen1);

					line.setLine(curr_x + plot_step_x, porog_max, curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					painter.drawLine(line);


					/*					painter.setBrush(brush1);

					poligon_max << QPointF(curr_x + plot_step_x, porog_max) << QPointF(curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					poligon_max_started = true;*/
					break;

				case 0:

					base_x_neg = curr_x + plot_step_x * ( prev_thickness - por_neg )/( prev_thickness - curr_thick );
					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );
					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );


					poligon_min << QPointF(base_x_neg,  0) << QPointF(base_x_neg_lim,  porog_min);
					painter.drawPolygon(poligon_min,fill_rule);
					poligon_min.clear();
					poligon_min_started = false;
					poligon_min_lower = false;


					painter.setPen(pen3);

					line.setLine( base_x_neg_lim,  porog_min, base_x_pos_lim,  porog_max);
					painter.drawLine(line);

					painter.setPen(pen1);


					line.setLine(base_x_pos_lim,  porog_max, curr_x + plot_step_x, (curr_thick - por_neg) * plot_step_thick_y);
					painter.drawLine(line);



					/*					painter.setBrush(brush1);

					poligon_max << QPointF(base_x_pos_lim,  porog_max) << QPointF(curr_x + plot_step_x, (curr_thick - por_neg) * plot_step_thick_y);
					poligon_max_started = true;*/
					break;


				case 1:

					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );
					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );

					poligon_min << QPointF(base_x_neg_lim,  porog_min);
					painter.drawPolygon(poligon_min,fill_rule);
					poligon_min.clear();
					poligon_min_started = false;


					painter.setPen(pen3);

					line.setLine( base_x_neg_lim,  porog_min, base_x_pos_lim,  porog_max);
					painter.drawLine(line);

					painter.setPen(pen1);

					line.setLine(base_x_pos_lim,  porog_max, curr_x + plot_step_x, (curr_thick - por_neg) * plot_step_thick_y);
					painter.drawLine(line);


					/*					painter.setBrush(brush1);

					poligon_max << QPointF(base_x_pos_lim,  porog_max) << QPointF(curr_x + plot_step_x, (curr_thick - por_neg) * plot_step_thick_y);
					poligon_max_started = true;*/
					break;


				case 2:

					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );

					line.setLine( curr_x,  ((prev_thickness - por_neg) * plot_step_thick_y), base_x_pos_lim,  porog_max);
					painter.drawLine(line);

					painter.setPen(pen1);

					line.setLine(base_x_pos_lim,  porog_max, curr_x + plot_step_x, (curr_thick - por_neg) * plot_step_thick_y);
					painter.drawLine(line);


					/*					painter.setBrush(brush1);


					poligon_max << QPointF(base_x_pos_lim,  porog_max) << QPointF(curr_x + plot_step_x, (curr_thick - por_neg) * plot_step_thick_y);
					poligon_max_started = true;*/

					break;

				case 3:

					line.setLine(curr_x, (prev_thickness - por_neg) * plot_step_thick_y, curr_x + plot_step_x, (curr_thick - por_neg) * plot_step_thick_y);
					painter.drawLine(line);


					//poligon_max << QPointF(curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					break;


				case 4:

					base_x_pos = curr_x + plot_step_x * ( prev_thickness - por_pos )/( prev_thickness - curr_thick );


					line.setLine(curr_x, (prev_thickness - por_neg) * plot_step_thick_y, base_x_pos,  max_y);
					painter.drawLine(line);

					line.setLine(base_x_pos,  max_y, curr_x + plot_step_x, ((curr_thick - por_neg) * plot_step_thick_y));
					painter.drawLine(line);

					/*					poligon_max << QPointF(base_x_pos,  max_y) << QPointF(curr_x + plot_step_x,  ((curr_thick - por_neg) * plot_step_thick_y));
					poligon_max_upper = false;*/

					break;

				default:;
				}
			}
			else
			{
				curr_area_count = 4;

				switch(prev_area_count)
				{
				case -1:

					painter.setPen(pen1);


					line.setLine(curr_x + plot_step_x, porog_max, curr_x + plot_step_x, max_y);
					painter.drawLine(line);


					/*					painter.setBrush(brush1);

					poligon_max << QPointF(curr_x + plot_step_x, porog_max) << QPointF(curr_x + plot_step_x, max_y);	// выше максимума
					poligon_max_started = true;
					poligon_max_upper = true;*/
					break;


				case 0:

					base_x_neg = curr_x + plot_step_x * ( prev_thickness - por_neg )/( prev_thickness - curr_thick );
					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );
					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );
					base_x_pos = curr_x + plot_step_x * ( prev_thickness - por_pos )/( prev_thickness - curr_thick );

					poligon_min << QPointF(base_x_neg,  0) << QPointF(base_x_neg_lim,  porog_min);
					painter.drawPolygon(poligon_min,fill_rule);
					poligon_min.clear();
					poligon_min_started = false;
					poligon_min_lower = false;



					painter.setPen(pen3);

					line.setLine( base_x_neg_lim,  porog_min, base_x_pos_lim,  porog_max);
					painter.drawLine(line);


					painter.setPen(pen1);


					line.setLine(base_x_pos_lim,  porog_max, base_x_pos,  max_y);
					painter.drawLine(line);

					line.setLine(base_x_pos,  max_y, curr_x + plot_step_x, max_y);
					painter.drawLine(line);


					/*					painter.setBrush(brush1);


					poligon_max << QPointF(base_x_pos_lim,  porog_max) << QPointF(base_x_pos,  max_y);
					poligon_max_started = true;
					poligon_max_upper = true;*/

					break;


				case 1:

					base_x_neg_lim = curr_x + plot_step_x * ( prev_thickness - min_val )/( prev_thickness - curr_thick );
					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );
					base_x_pos = curr_x + plot_step_x * ( prev_thickness - por_pos )/( prev_thickness - curr_thick );

					poligon_min << QPointF(base_x_neg_lim,  porog_min);
					painter.drawPolygon(poligon_min,fill_rule);
					poligon_min.clear();
					poligon_min_started = false;



					painter.setPen(pen3);

					line.setLine( base_x_neg_lim,  porog_min, base_x_pos_lim,  porog_max);
					painter.drawLine(line);

					painter.setPen(pen1);


					line.setLine(base_x_pos_lim,  porog_max, base_x_pos,  max_y);
					painter.drawLine(line);

					line.setLine(base_x_pos,  max_y, curr_x + plot_step_x, max_y);
					painter.drawLine(line);

					/*					painter.setBrush(brush1);

					poligon_max << QPointF(base_x_pos_lim,  porog_max) << QPointF(base_x_pos,  max_y);
					poligon_max_started = true;
					poligon_max_upper = true;*/

					break;

				case 2:

					base_x_pos_lim = curr_x + plot_step_x * ( prev_thickness - max_val )/( prev_thickness - curr_thick );
					base_x_pos = curr_x + plot_step_x * ( prev_thickness - por_pos )/( prev_thickness - curr_thick );

					line.setLine( curr_x,  ((prev_thickness - por_neg) * plot_step_thick_y), base_x_pos_lim,  porog_max);
					painter.drawLine(line);

					painter.setPen(pen1);


					line.setLine(base_x_pos_lim,  porog_max, base_x_pos,  max_y);
					painter.drawLine(line);

					line.setLine(base_x_pos,  max_y, curr_x + plot_step_x, max_y);
					painter.drawLine(line);


					/*					painter.setBrush(brush1);

					poligon_max << QPointF(base_x_pos_lim,  porog_max) << QPointF(base_x_pos,  max_y);
					poligon_max_started = true;
					poligon_max_upper = true;*/

					break;

				case 3:

					base_x_pos = curr_x + plot_step_x * ( prev_thickness - por_pos )/( prev_thickness - curr_thick );


					line.setLine(curr_x, ((prev_thickness - por_neg) * plot_step_thick_y), base_x_pos,  max_y);
					painter.drawLine(line);

					line.setLine(base_x_pos, max_y, curr_x + plot_step_x, max_y);
					painter.drawLine(line);

					/*					poligon_max << QPointF(curr_x,  ((prev_thickness - por_neg) * plot_step_thick_y)) << QPointF(base_x_pos, max_y);
					poligon_max_upper = true;*/

					break;

				case 4:

					line.setLine(curr_x,  max_y, curr_x + plot_step_x, max_y);
					painter.drawLine(line);

					/*					poligon_max << QPointF(curr_x + plot_step_x,  max_y);	// выше максимума
					poligon_max_upper = true;*/

					break;

				default:;
				}

			}



			//			float max_thick = p_thick_info->thick.max_thick;
			float max_thick = thick_elem->thick.max_thick;

			bool max_in_possible = (max_thick >= min_val);

			bool both_max_possible = (prev_max_in_possible && max_in_possible);



			QPen old_pen = painter.pen();
			QBrush old_brush = painter.brush();

			if(max_thick > max_val)
			{
				if(max_thick > por_pos)
				{
					curr_max_area_n = 4;

					switch(prev_max_area_n)
					{
					case -1:
						poligon_max << QPointF(curr_x + plot_step_x, porog_max) << QPointF(curr_x + plot_step_x, max_y);	// выше максимума
						poligon_max_started = true;
						poligon_max_upper = true;

						break;

					case 2:
						base_x_pos_lim = curr_x + plot_step_x * ( prev_max_thickness - max_val )/( prev_max_thickness - max_thick );
						base_x_pos = curr_x + plot_step_x * ( prev_max_thickness - por_pos )/( prev_max_thickness - max_thick );


						if(both_max_possible)
						{
							line.setLine( curr_x,  ((prev_max_thickness - por_neg) * plot_step_thick_y), base_x_pos_lim,  porog_max);
							painter.setPen(pen4);
							painter.drawLine(line);
						}

						poligon_max << QPointF(base_x_pos_lim,  porog_max) << QPointF(base_x_pos,  max_y);
						poligon_max_started = true;
						poligon_max_upper = true;
						break;


					case 3:

						base_x_pos = curr_x + plot_step_x * ( prev_max_thickness - por_pos )/( prev_max_thickness - max_thick );

						poligon_max << QPointF(curr_x,  ((prev_max_thickness - por_neg) * plot_step_thick_y)) << QPointF(base_x_pos, max_y);
						poligon_max_upper = true;

						break;

					case 4:

						poligon_max << QPointF(curr_x + plot_step_x,  max_y);	// выше максимума
						poligon_max_upper = true;
						break;

					default:;
					}
				}
				else
				{
					curr_max_area_n = 3;

					switch(prev_max_area_n)
					{
					case -1:

						poligon_max << QPointF(curr_x + plot_step_x,  porog_max) << QPointF(curr_x + plot_step_x, (max_thick - por_neg) * plot_step_thick_y);
						poligon_max_started = true;

						break;

					case 2:
						base_x_pos_lim = curr_x + plot_step_x * ( prev_max_thickness - max_val )/( prev_max_thickness - max_thick );

						if(both_max_possible)
						{
							line.setLine( curr_x,  ((prev_max_thickness - por_neg) * plot_step_thick_y), base_x_pos_lim,  porog_max);
							painter.setPen(pen4);
							painter.drawLine(line);
						}

						poligon_max << QPointF(base_x_pos_lim,  porog_max) << QPointF(curr_x + plot_step_x, (max_thick - por_neg) * plot_step_thick_y);
						poligon_max_started = true;
						break;

					case 3:

						poligon_max << QPointF(curr_x + plot_step_x, ((max_thick - por_neg) * plot_step_thick_y));
						break;

					case 4:

						base_x_pos = curr_x + plot_step_x * ( prev_max_thickness - por_pos )/( prev_max_thickness - max_thick );

						poligon_max << QPointF(base_x_pos,  max_y) << QPointF(curr_x + plot_step_x,  ((max_thick - por_neg) * plot_step_thick_y));
						poligon_max_upper = false;
						break;

					default:;

					}
				}
			}
			else
			{
				curr_max_area_n = 2;

				switch(prev_max_area_n)
				{
				case 2:
					if(both_max_possible)
					{
						line.setLine( curr_x,  ((prev_max_thickness - por_neg) * plot_step_thick_y), curr_x + plot_step_x, ((max_thick - por_neg) * plot_step_thick_y) );
						painter.setPen(pen4);
						painter.drawLine(line);
					}
					else if(max_in_possible)
					{
						line.setLine( curr_x,  porog_min, curr_x + plot_step_x, ((max_thick - por_neg) * plot_step_thick_y) );
						painter.setPen(pen4);
						painter.drawLine(line);

					}
					else if(prev_max_in_possible)
					{
						line.setLine( curr_x,  ((prev_max_thickness - por_neg) * plot_step_thick_y), curr_x + plot_step_x, porog_min );
						painter.setPen(pen4);
						painter.drawLine(line);
					}
					break;


				case 3:

					base_x_pos_lim = curr_x + plot_step_x * ( prev_max_thickness - max_val )/( prev_max_thickness - max_thick );

					poligon_max << QPointF(base_x_pos_lim,  porog_max);

					painter.setPen(pen1);
					painter.setBrush(brush1);

					painter.drawPolygon(poligon_max,fill_rule);

					poligon_max.clear();
					poligon_max_started = false;

					if(max_in_possible)
					{
						line.setLine( base_x_pos_lim,  porog_max, curr_x + plot_step_x, ((max_thick - por_neg) * plot_step_thick_y) );
						painter.setPen(pen4);
						painter.drawLine(line);
					}
					else
					{
						line.setLine( base_x_pos_lim,  porog_max, curr_x + plot_step_x, porog_min );
						painter.setPen(pen4);
						painter.drawLine(line);
					}
					break;

				case 4:

					base_x_pos = curr_x + plot_step_x * ( prev_max_thickness - por_pos )/( prev_max_thickness - max_thick );
					base_x_pos_lim = curr_x + plot_step_x * ( prev_max_thickness - max_val )/( prev_max_thickness - max_thick );

					poligon_max << QPointF(base_x_pos,  max_y) << QPointF(base_x_pos_lim, porog_max);

					painter.setPen(pen1);
					painter.setBrush(brush1);

					painter.drawPolygon(poligon_max,fill_rule);


					poligon_max.clear();
					poligon_max_started = false;
					poligon_max_upper = false;


					if(max_in_possible)
					{
						line.setLine( base_x_pos_lim,  porog_max, curr_x + plot_step_x, ((max_thick - por_neg) * plot_step_thick_y) );
						painter.setPen(pen4);
						painter.drawLine(line);
					}
					else
					{
						line.setLine( base_x_pos_lim,  porog_max, curr_x + plot_step_x, porog_min );
						painter.setPen(pen4);
						painter.drawLine(line);
					}

					break;

				default:;

				}
			}


			painter.setPen(old_pen);
			painter.setBrush(old_brush);


			prev_max_in_possible = max_in_possible;

			prev_thickness = curr_thick;



			prev_max_area_n = curr_max_area_n;
			prev_max_thickness = max_thick;


		}

		else
		{
			if(poligon_min_started)
			{
				if(poligon_min_lower)
				{
					poligon_min << QPointF(curr_x, 0);
					poligon_min_lower = false;
				}
				poligon_min << QPointF(curr_x, porog_min);
				painter.drawPolygon(poligon_min,fill_rule);
				poligon_min.clear();
				poligon_min_started = false;
			}


			if(poligon_max_started)
			{
				if(poligon_max_upper)
				{
					poligon_max << QPointF(curr_x, max_y);
					poligon_max_upper = false;
				}
				poligon_max << QPointF(curr_x, porog_max);

				painter.setPen(pen1);
				painter.setBrush(brush1);
				painter.drawPolygon(poligon_max,fill_rule);

				poligon_max.clear();
				poligon_max_started = false;
			}


			curr_area_count = -1;

			curr_max_area_n = -1;


		}


		prev_area_count = curr_area_count;

		curr_x += plot_step_x;

	}

	if(poligon_min_started)
	{
		if(poligon_min_lower)
			poligon_min << QPointF(curr_x, 0);

		poligon_min << QPointF(curr_x, porog_min);
		painter.drawPolygon(poligon_min,fill_rule);
		poligon_min.clear();
		poligon_min_started = false;
	}

	poligon_min.clear();

	if(poligon_max_started)
	{
		if(poligon_max_upper)
			poligon_max << QPointF(curr_x, max_y);
		poligon_max << QPointF(curr_x, porog_max);

		painter.setPen(pen1);
		painter.setBrush(brush1);

		painter.drawPolygon(poligon_max,fill_rule);
		poligon_max.clear();
	}

	poligon_max.clear();
#if 0
#endif

}

void PlottersWidget::PlotDefect(QPainter & painter, const QRect& content_rect,const quint8 chan)
{
	QColor back_color(Qt::red);
	back_color.setAlpha(30);
	painter.fillRect(content_rect,back_color);
	painter.save();
	painter.translate(1,0);
	painter.drawEllipse(QRect(QPoint(0,0),QSize(5,3)));//контрольная точка начала координат
	float pixmap_height=content_rect.height();
	float pixmap_width=content_rect.width();
	float left_tab=content_rect.left();
	float plot_step_y = (pixmap_height - 1)/ (float)MaxAmpl;
	float plot_step_x=3.0;
	const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(chan);
	const par_strb_info_t *strb_chan_info = _deviceSettings->getStrobInfoArray(chan);


	QColor SubStrobsColor[NUM_STRBS][NUM_STRBS_EXTRA+1];		// по уровням 


	for(quint8 i = 1; i < NUM_STRBS; i++)		// первый строб пропускается
	{
		if(strb_chan_info[i].on_extra_por)
		{
			int hue;
			int strat;
			int value;
			QColor tmp_Color=_deviceSettings->getStrobColor().at(i);
			tmp_Color.getHsv(&hue, &strat, &value);

			SubStrobsColor[i][0] = QColor::fromHsv(hue, 0.4f*strat, 0.5f*(255-value)+value);
			SubStrobsColor[i][1] = QColor::fromHsv(hue, 0.6f*strat, 0.25f*(255-value)+value);
			SubStrobsColor[i][2] =  tmp_Color;
		}
		else
			SubStrobsColor[i][0] =_deviceSettings->getStrobColor().at(i);
	}
	int requested_size=pixmap_width/plot_step_x+1;
	int beg=0;

	float curr_x = 0;
	float base_y = pixmap_height;

	float next_x = curr_x + plot_step_x/2;
//PlotDefectElement lambda
#if 1
	auto PlotDefectElement=[=](QPainter& painter,const DefectElement* def_elem, float curr_x,const float next_x)
	{
		if(!def_elem->filled)
			return;

		// отрисовка включенных стробов в порядке возрастания амплитуды, за исключением сигнала АК, который рисуется линией на заднем плане (?) + закраской на переднем


		const float base_y = pixmap_height;


		// отрисовка стробов в порядке убывания амплитуды (в виде прямоугольников от 0 до strob_data.ampl)

		bool any_def = false;

		QColor strob_fill_color;

		QRectF rect;
		QRect rect2;
		std::vector<std::pair<quint8,sum_strob_info_t>> sorted_strobs;
		quint8 index_strob=0;
		for(auto elem=def_elem->strobs.begin();elem!=def_elem->strobs.end();++elem)
		{
			sorted_strobs.push_back(std::make_pair(index_strob++,*elem));
		}
		std::sort(sorted_strobs.begin(),sorted_strobs.end(),[](const std::pair<quint8, sum_strob_info_t>& a,const std::pair<quint8, sum_strob_info_t>& b)  {
			return a.second.strob_data.ampl > b.second.strob_data.ampl;});/**/
			for( auto pos=sorted_strobs.begin();pos!=sorted_strobs.end();++pos)
			{
				//qDebug()<<"Index:"<<pos->first<<" Ampl:"<< pos->second.strob_data.ampl;
				rect.setCoords(curr_x, base_y - pos->second.strob_data.ampl*plot_step_y, next_x, base_y);
				strob_fill_color=_deviceSettings->getStrobColor().at(pos->first);
				painter.fillRect(rect, strob_fill_color);
			}

	};
#endif
	QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
	if(requested_size<elem_list.count())
	{
		beg=elem_list.count()-requested_size;
	}

	for(int j = beg; j < elem_list.count(); j++)
	{
		bool thick_filled = false;


		DefectElement* def_elem;
	/*	for(int jj=0;jj<_elem_list[j]->chan_info_array.count();jj++)
		{
			if(((jj+1)%2==0))
			{*/
				def_elem=static_cast<DefectElement*>(elem_list[j]->chan_info_array[chan]);
	//		}
		//}
		PlotDefectElement(painter,def_elem,curr_x,next_x);
		curr_x = next_x;
		next_x = curr_x + plot_step_x;

	}
	QPen pen0;
	QVector<qreal> dash_paretten;
	dash_paretten << 4 << (3*(NUM_STRBS_EXTRA+1)*NUM_STRBS - 3);
	pen0.setDashPattern(dash_paretten);

	QPen pen1;
	dash_paretten.clear();
	dash_paretten << 2 << (3*(NUM_STRBS_EXTRA+1)*NUM_STRBS - 1);
	pen1.setDashPattern(dash_paretten);

	QPen pen2(Qt::white);
	dash_paretten.clear();
	dash_paretten << 1 << (3*(NUM_STRBS_EXTRA+1)*NUM_STRBS);
	pen2.setDashPattern(dash_paretten);


	int offset = 0;
	QLineF line_base(left_tab, pixmap_height, pixmap_width, pixmap_height);


	auto PlotStrobPorLevel=[](QPainter & painter, 
		QPen &pen,
		const QColor &col,
		QPen &back_pen,
		const QLineF &line,
		int &offset)
	{
		pen.setColor(col);
		pen.setDashOffset(++offset);
		painter.setPen(pen);
		painter.drawLine(line);

		++offset;
		back_pen.setDashOffset(++offset);
		painter.setPen(back_pen);
		painter.drawLine(line);
	};
	auto PorLabel=[=](QPainter& painter,quint8 porog)
	{
		painter.save();
		painter.translate(0,MaxAmpl*plot_step_y-porog*plot_step_y);
		painter.setPen(Qt::black);
		painter.drawText(QRect(0,0,100,50),tr("%1").arg(porog));
		painter.restore();
	};

	for(quint8 i = 0; i < NUM_STRBS; i++)
	{
		if(strb_par[i].on_strb)	// наличие многоуровневого строба не важно, важна абс. амплитуда строба
		{
			if(strb_chan_info[i].on_extra_por)
			{
				PlotStrobPorLevel(painter, pen1, SubStrobsColor[i][0], pen2, line_base.translated(0, -strb_par[i].por*plot_step_y), offset);
				PorLabel(painter,strb_par[i].por);

				for(quint8 j = 0; j < NUM_STRBS_EXTRA; j++)
				{
					PlotStrobPorLevel(painter, pen1, SubStrobsColor[i][j+1], pen2, line_base.translated(0, -strb_chan_info[i].extra_por[j]*plot_step_y), offset);
					PorLabel(painter,strb_chan_info[i].extra_por[j]);
				}

			}
			else
				PlotStrobPorLevel(painter, pen0, _deviceSettings->getStrobColor().at(i), pen2, line_base.translated(0, -strb_par[i].por*plot_step_y), offset);

		}
	}
	painter.restore();

}

void PlottersWidget::PlotThickLam(QPainter & painter, const QRect& content_rect,const quint8 chan)
{
	float pixmap_height=content_rect.height();
	float pixmap_width=content_rect.width();
	float left_tab=content_rect.left();
	float plot_step_y = (pixmap_height - 1)/ (float)MaxAmpl;
	float plot_step_x=3.0;
	painter.save();
	painter.translate(1,0);
	/*auto plot_lam_porog=[&](QPainter& painter)*/
#if 1
	auto plot_lam_porog=[&](QPainter& painter)
	{
	const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(chan);
	QPen pen;
	pen.setWidth(2);
	QVector<qreal> dash_paretten;
	dash_paretten << 3 << 10;
	pen.setDashPattern(dash_paretten);
	const float base_y = pixmap_height;
	const quint8 strob_porog = strb_par[2].por;
	pen.setColor(Qt::darkGray);
	
	float porog = base_y - strob_porog * plot_step_y;
	painter.setPen(pen);
	QLineF dash_line( left_tab + 1,  porog, pixmap_width - 1,  porog);
	painter.drawLine(dash_line);

	};
#endif

const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(chan);
	

	if(strb_par[2].on_strb)	// отрисовка развёртки амплитуды сигнала в этом стробе
	{
		
		int requested_size=pixmap_width/plot_step_x+1;
	int beg=0;

	float curr_x = 0;
	float base_y = pixmap_height;

	float next_x = curr_x + plot_step_x/2;
//PlotThicklamElement lambda
#if 1
	auto PlotThicklamElement=[=](QPainter& painter,const ThickLamElement* thick_lam_elem, float curr_x,const float next_x)
	{
		painter.save();
		
		if(!thick_lam_elem->filled)
			return;


		const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(chan);
		const quint8 strob_porog = strb_par[2].por;
		const float base_y = pixmap_height;




		bool any_def = false;

		QColor strob_fill_color;

		QRectF rect;

		if(thick_lam_elem->strob_data[2].ampl>strob_porog){
			float strob_base_y=base_y -strob_porog*plot_step_y;

			rect.setCoords(curr_x, strob_base_y  - (thick_lam_elem->strob_data[2].ampl-strob_porog)*plot_step_y, next_x, strob_base_y);
			strob_fill_color=QColor(Qt::green);
			painter.fillRect(rect, strob_fill_color);
		}
		painter.restore();
	};
#endif

//PlotErrorSemiTrans lambda
#if 1
auto PlotErrorSemiTrans=[=](QPainter & painter, 
								const quint8 &defect_flag,
								const float curr_x,
								const float next_x,
								const int curr_y_b,
								const int curr_height)
{
	painter.save();
	
	if((defect_flag & (ERROR_FLAG_NO_AK|ERROR_FLAG_LAMINATION)) == (ERROR_FLAG_NO_AK|ERROR_FLAG_LAMINATION))
	{
		// вверху - расслоение, ниже - потеря АК

	/*	painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height/2),_deviceSettings->getIncorrectColor("ERROR_FLAG_LAMINATION") );
		painter.fillRect(QRectF(curr_x, curr_y_b + curr_height/2, next_x - curr_x, curr_height/2), _deviceSettings->getIncorrectColor("ERROR_FLAG_NO_AK") );*/
	}
	else
	{
		if(defect_flag & ERROR_FLAG_LAMINATION)
			painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height), _deviceSettings->getIncorrectColor("ERROR_FLAG_LAMINATION") );

		if(defect_flag & ERROR_FLAG_NO_AK)
			painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height), _deviceSettings->getIncorrectColor("ERROR_FLAG_NO_AK") );
	}



	if(defect_flag & ERROR_FLAG_DATA_SKIP)
		painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height), _deviceSettings->getIncorrectColor("ERROR_FLAG_DATA_SKIP") );
	if(defect_flag & ERROR_FLAG_INCORRECT)
		painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height), _deviceSettings->getIncorrectColor("ERROR_FLAG_INCORRECT")  );

	painter.restore();
};
#endif	
QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
	if(requested_size<elem_list.count())
	{
		beg=elem_list.count()-requested_size;
	}

	for(int j = beg; j < elem_list.count(); j++)
	{
		bool thick_filled = false;


		ThickLamElement* thick_lam_element=static_cast<ThickLamElement*>(elem_list[j]->chan_info_array[chan]);
	
		PlotThicklamElement(painter,thick_lam_element,curr_x,next_x);
		PlotErrorSemiTrans(painter,thick_lam_element->error_flags,curr_x,next_x,0,pixmap_height);
		
		curr_x = next_x;
		next_x = curr_x + plot_step_x;

	}
		plot_lam_porog(painter);
		PlotThick(painter,content_rect,chan);
	}
	painter.restore();
}
