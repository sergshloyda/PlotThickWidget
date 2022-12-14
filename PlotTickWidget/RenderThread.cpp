#include "RenderThread.h"
#include "qimage.h"
#include "qpainter.h"
void RenderThread::rendering(int w,int h, QList<Element_Info*> list)
{
	//qDebug()<<"Process slot w:"<<w<<" h:"<<h<<" cnt:"<<cnt;

	// emit onDrawTriangle(drawMyTriangle(w,h,cnt));
	emit onDraw(_draw_strategy->Draw(w,h,list));
}
QImage DrawDefectRow::Draw(int w,int h,const QList<Element_Info*>& list)
{
	QImage img( w, h, QImage::Format_RGB888 );
	img.fill( Qt::white );
	QPainter painter;
	painter.begin( &img );

	painter.save();
	//painter.setRenderHint(QPainter::Antialiasing, true);
	painter.translate(2,0);

	float pixmap_height=(float)h;
	float pixmap_width=(float)w;
	float left_tab=2;
	const quint8 MaxAmpl=255;
	float plot_step_y = (pixmap_height - 1)/ (float)MaxAmpl;
	float plot_step_x=3.0;
	const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(_num_chan);
	const par_strb_info_t *strb_chan_info = _deviceSettings->getStrobInfoArray(_num_chan);


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
	int elements_count=0;

	elements_count=list.count();


	if(requested_size<elements_count)
	{
		beg=elements_count-requested_size;
	}

	for(int j = beg; j < elements_count; j++)
	{
		bool thick_filled = false;


		DefectElement* def_elem;
		/*	for(int jj=0;jj<_elem_list[j]->chan_info_array.count();jj++)
		{
		if(((jj+1)%2==0))
		{*/
		///_draw_mutex->lock();
		def_elem=static_cast<DefectElement*>(list.at(j)->chan_info_array.at(_num_chan));
		///_draw_mutex->unlock();
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
		painter.setFont(QFont("Arial", 9, QFont::Bold));
		painter.drawText(QRect(0,0,100,50),qApp->trUtf8("%1").arg(porog));
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
	painter.end();

	return img;
}

QPixmap DrawDefectRow::DrawPixmap(int w,int h,const QList<Element_Info*>& list)
{
	/***определение вспомогоательных функций**/
	//PlotDefectElement lambda
#if 1
	auto PlotDefectElement=[=](QPainter& painter,const DefectElement* def_elem, float curr_x,const float next_x,const float pixmap_height,const float plot_step_y)
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

	//PlotStrobPorLevel
#if 1
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


	auto PorLabel=[=](QPainter& painter,const quint8 porog,const quint8 MaxAmpl,const float plot_step_y)
	{
		painter.save();
		painter.translate(0,MaxAmpl*plot_step_y-porog*plot_step_y);
		painter.setPen(Qt::black);
		painter.setFont(QFont("Arial", 7));
		painter.drawText(QRect(0,0,100,50),qApp->trUtf8("%1").arg(porog));
		painter.restore();
	};
#endif
	//setSubStrobsColors
#if 1
	auto setSubStrobsColors=[=](QColor sub_strob_color_array[][3],const par_strb_info_t *strb_chan_info)
	{

			for(quint8 i = 1; i < NUM_STRBS; i++)		// первый строб пропускается
	{
		if(strb_chan_info[i].on_extra_por)
		{
			int hue;
			int strat;
			int value;
			QColor tmp_Color=_deviceSettings->getStrobColor().at(i);
			tmp_Color.getHsv(&hue, &strat, &value);

			sub_strob_color_array[i][0] = QColor::fromHsv(hue, 0.4f*strat, 0.5f*(255-value)+value);
			sub_strob_color_array[i][1] = QColor::fromHsv(hue, 0.6f*strat, 0.25f*(255-value)+value);
			sub_strob_color_array[i][2] =  tmp_Color;
		}
		else
			sub_strob_color_array[i][0] =_deviceSettings->getStrobColor().at(i);
	}
	};
#endif
	QPixmap pixmap(w,h);
	pixmap.fill(Qt::white);
	QPainter painter;
	painter.begin(&pixmap);;
	painter.drawRect(1,1,w-1,h-1);
	painter.save();
	painter.translate(1,1);

	float pixmap_height=(float)h;
	float pixmap_width=(float)w;
	float left_tab=0;
	const quint8 MaxAmpl=255;
	float plot_step_y = (pixmap_height - 1)/ (float)MaxAmpl;
	float plot_step_x=3.0;
	const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(_num_chan);
	const par_strb_info_t *strb_chan_info = _deviceSettings->getStrobInfoArray(_num_chan);
	
	QColor SubStrobsColor[NUM_STRBS][NUM_STRBS_EXTRA+1];		// по уровням 

	setSubStrobsColors(SubStrobsColor,strb_chan_info);

	int requested_size=pixmap_width/plot_step_x+1;
	/*int beg=0;
	float curr_x = 0;*/
	float base_y = pixmap_height;
	//float next_x = curr_x + plot_step_x/2;
	
	int elements_count=0;

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
	float curr_x = left_tab;
	float next_x = left_tab + plot_step_x/2;
	if(list.count()>0)
	{
		/*DefectElement* def_elem;
		def_elem=;*/
		PlotDefectElement(painter,
			static_cast<DefectElement*>(list.at(_beg_index-1)->chan_info_array.at(_num_chan)),
			curr_x,next_x,pixmap_height,plot_step_y);

	elements_count=list.count();
	if(requested_size<elements_count)
	{
		_beg_index=elements_count-requested_size;
	}
	for(int j = _beg_index; j < elements_count; j++)
	{
		bool thick_filled = false;
		DefectElement* def_elem;
		def_elem=static_cast<DefectElement*>(list.at(j)->chan_info_array.at(_num_chan));
		PlotDefectElement(painter,def_elem,curr_x,next_x,pixmap_height,plot_step_y);
		curr_x = next_x;
		next_x = curr_x + plot_step_x;
	}
	}
	
	for(quint8 i = 0; i < NUM_STRBS; i++)
	{
		if(strb_par[i].on_strb)	// наличие многоуровневого строба не важно, важна абс. амплитуда строба
		{
			if(strb_chan_info[i].on_extra_por)
			{
				PlotStrobPorLevel(painter, pen1, SubStrobsColor[i][0], pen2, line_base.translated(0, -strb_par[i].por*plot_step_y), offset);
				//PorLabel(painter,strb_par[i].por);
				for(quint8 j = 0; j < NUM_STRBS_EXTRA; j++)
				{
					PlotStrobPorLevel(painter, pen1, SubStrobsColor[i][j+1], pen2, line_base.translated(0, -strb_chan_info[i].extra_por[j]*plot_step_y), offset);
					//	PorLabel(painter,strb_chan_info[i].extra_por[j]);
				}
			}
			else
				PlotStrobPorLevel(painter, pen0, _deviceSettings->getStrobColor().at(i), pen2, line_base.translated(0, -strb_par[i].por*plot_step_y), offset);
		}
	}
	painter.restore();
	painter.end();
	return pixmap;
}
QPixmap DrawThickRow::DrawPixmap(int w,int h,const QList<Element_Info*>& elem_list)
{

	QPixmap pixmap(w,h);
	pixmap.fill(Qt::white);
	QPainter painter(&pixmap);
	if((_deviceSettings->getChanMode(_num_chan)!=TD_TOL) && (_deviceSettings->getChanMode(_num_chan)!=TD_TOL_LAM))return QPixmap();
	float norm_val = 10.0;

	const Qt::FillRule fill_rule=Qt::WindingFill;





	float por_pos = 0;
	float por_neg = 0;

	float curr_range;

	float min_val = 8.0;
	float max_val = 12.0;

	float thick_range_koef=0.2;
	float pixmap_height=(float)h;
	float pixmap_width=(float)w;
	float left_tab=0;



	curr_range = max_val * (1 + thick_range_koef);

	por_neg = 0;
	por_pos = curr_range;





	const float plot_step_thick_y = (pixmap_height - 1) / curr_range;
	const float porog_max = (max_val - por_neg) * plot_step_thick_y;
	painter.drawRect(1,1,w-2,h-2);
	painter.save();
	painter.translate(2,2);
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


		thick_elem=static_cast<ThickElement*>(elem_list[j]->chan_info_array[_num_chan]);




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
	return pixmap;


}
QImage DrawThickRow::Draw(int w,int h,const QList<Element_Info*>& elem_list)
{
	return QImage();
}
QImage DrawThickLamRow::Draw(int w,int h,const QList<Element_Info*>& elem_list)
{
	return QImage();
}
QPixmap DrawThickLamRow::DrawPixmap(int w,int h,const QList<Element_Info*>& elem_list)
{

	QPixmap pixmap(w,h);
	pixmap.fill(Qt::white);
	QPainter painter(&pixmap);
	float pixmap_height=(float)h;
	float pixmap_width=(float)w;
	float left_tab=0;
	const quint8 MaxAmpl=255;
	float plot_step_y = (pixmap_height - 1)/ (float)MaxAmpl;
	float plot_step_x=3.0;
	painter.drawRect(1,1,w-2,h-2);
	painter.save();
	painter.translate(2,2);
	/*auto plot_lam_porog=[&](QPainter& painter)*/
#if 1
	auto plot_lam_porog=[&](QPainter& painter)
	{
		const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(_num_chan);
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
	//PlotThicklamElement lambda
#if 1
	auto PlotThicklamElement=[=](QPainter& painter,const ThickLamElement* thick_lam_elem, float curr_x,const float next_x)
	{
		painter.save();

		if(!thick_lam_elem->filled)
			return;


		const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(_num_chan);
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
	//PlotThick lambda
#if 1
	auto PlotThick=[=](QPainter & painter,const quint8 nChan)
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
		float pixmap_height=(float)h;
		float pixmap_width=(float)w;
		float left_tab=0;



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
		//QList<Element_Info*> elem_list=qApp->property("ElementList").value<QList<Element_Info*>>();
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


	};
#endif
	const par_strb_t *strb_par = _deviceSettings->getAmplStrobArray(_num_chan);


	if(strb_par[2].on_strb)	// отрисовка развёртки амплитуды сигнала в этом стробе
	{

		int requested_size=pixmap_width/plot_step_x+1;
		int beg=0;

		float curr_x = 0;
		float base_y = pixmap_height;

		float next_x = curr_x + plot_step_x/2;

		if(requested_size<elem_list.count())
		{
			beg=elem_list.count()-requested_size;
		}

		for(int j = beg; j < elem_list.count(); j++)
		{
			bool thick_filled = false;


			ThickLamElement* thick_lam_element=static_cast<ThickLamElement*>(elem_list[j]->chan_info_array[_num_chan]);

			PlotThicklamElement(painter,thick_lam_element,curr_x,next_x);
			PlotErrorSemiTrans(painter,thick_lam_element->error_flags,curr_x,next_x,0,pixmap_height);

			curr_x = next_x;
			next_x = curr_x + plot_step_x;

		}
		plot_lam_porog(painter);
		PlotThick(painter,_num_chan);
	}
	painter.restore();
	return pixmap;
}
QImage DrawMnemoRow::Draw(int w,int h,const QList<Element_Info*>& elem_list)
{
	return QImage();
}
DrawMnemoRow::DrawMnemoRow(DeviceSettings* device_settings):DrawStrategy(device_settings),_beg_index(1)
{
	_mnemo_background_color=_deviceSettings->getOscColor("MNEMO_BACKGROUND");
	_error_color=_deviceSettings->getOscColor("ERROR");
	_thick_color=_deviceSettings->getOscColor("THICK_COLOR");
	_sufficient_condition_color=_deviceSettings->getOscColor("SUFFICIENT_CONDITION");
	_sep_line_color=_deviceSettings->getOscColor("SEP_LINE_COLOR");
	_flaw_poper_color=_deviceSettings->getOscColor("FLAW_POPER_COLOR");
	_flaw_prod_color=_deviceSettings->getOscColor("FLAW_PROD_COLOR");
	_osc_background_color=_deviceSettings->getOscColor("OSC_BACKGROUND");


}
QPixmap DrawMnemoRow::DrawPixmap(int w,int h,const QList<Element_Info*>& elem_list)
{
	/*SetupMnemoRowDim;PlotMnemoRowsLine lambda в зависимости от выбранного количества слоев, делит виджет на равные части*/
#if 1
	auto SetupMnemoRowDim=[]( std::vector<int>& row_base, std::vector<int>& row_height,const int num_mnemo_rows,const float pix_h_step)
	{
		row_base[0] = 0;

		for(int i = 1; i <= num_mnemo_rows; i++)
		{
			row_base[i] = i*pix_h_step;
			row_height[i - 1] = row_base[i] - row_base[i-1];
			(row_base[i])++;//оставим пиксель для отрисовки линии
		}
	};

	auto PlotMnemoRowsLine=[=](QPainter& painter,const std::vector<int>& row_base,const int num_mnemo_rows)
	{
		QPen pen(_sep_line_color);
		painter.save();
		painter.setPen(pen);
		for(int i = 1; i <= num_mnemo_rows; i++)
		{

			painter.drawLine(0, row_base[i], w, row_base[i]);

		}
		painter.restore();
	};
#endif//SetupMnemoRowDim PlotMnemoRowsLine lambda

	/*PlotThickLevel lambda отрисовывает уровни допустимых толщин сверху вниз:(верх-минимальная толщина;середина-норма;низ-максимальная допустимая тощина)*/
#if 1
	auto PlotThickLevel=[=](QPainter& painter,const int curr_y_b,const int curr_height,const float thick_range_coefficient)
	{
		const par_thick_t& thick_params=_deviceSettings->getThickParams();
		const float norm_val=thick_params.thick*0.01f;
		float min_val = 0;
		float max_val = 0;
		float por_neg = 0.0;

		if(thick_params.thick_lim_relative)
		{
			min_val = norm_val * (1.0f - thick_params.thick_lim_rel_neg * 0.001f);
			max_val = norm_val * (1.0f + thick_params.thick_lim_rel_pos * 0.001f);
		}
		else
		{
			min_val = norm_val - thick_params.thick_lim_neg * 0.01f;
			max_val = norm_val + thick_params.thick_lim_pos * 0.01f;
		}

		float curr_range = max_val * (1 + thick_range_coefficient);

		const float base_y = curr_y_b;//верхняя граница отрисовки
		const float end_y = curr_y_b + curr_height - 1;//нижняя граница
		// толщина строится сверху вниз, а не снизу вверх
		const float plot_step_thick_y = (curr_height - 1) / curr_range;//пикселей на единицу толщины
		const float porog_max = base_y + (max_val - por_neg) * plot_step_thick_y;//уровень линии максимума
		const float porog_min = base_y + (min_val - por_neg) * plot_step_thick_y;//минимума
		const float porog_opt = base_y + (norm_val - por_neg) * plot_step_thick_y;//оптимальный
		const float left_tab=0.0f;
		const float pixmap_width=(float)w;
		QPen pen_dash;
		QVector<qreal> dash_paretten;
		dash_paretten << 3 << 10;
		pen_dash.setDashPattern(dash_paretten);

		pen_dash.setColor(_thick_color);
		painter.setPen(pen_dash);
		QLineF dash_line( left_tab,  porog_max, pixmap_width,  porog_max);
		painter.drawLine(dash_line);


		pen_dash.setColor(_error_color);
		painter.setPen(pen_dash);
		dash_line.setLine( left_tab + 2,  porog_min, pixmap_width,  porog_min);
		painter.drawLine(dash_line);


		pen_dash.setColor(_sufficient_condition_color);
		painter.setPen(pen_dash);
		dash_line.setLine( left_tab + 1,  porog_opt, pixmap_width,  porog_opt);
		painter.drawLine(dash_line);

	};
#endif//PlotThickLevel

	/*PlotMnemoThickElement lambda заполняет прямоугольник толщины(за начало - верх) цвет:зеленый толщина в допуске;
	коричневый-толщина превышает допустимую;красный-толщина ниже допустимой*/
#if 1//PlotMnemoThickElement lambda
	auto PlotMnemoThickElement=[=](QPainter& painter,
		const Element_Info* elem_info,
		const float curr_x,
		const float next_x,
		const int curr_y_b,
		const int curr_height,
		const float thick_range_coefficient)
	{

		const thick_values_t &sum_thick = elem_info->sum_defect.sum_thick;
		float por_neg = 0.0;
		float min_val = 0;
		float max_val = 0;
		const par_thick_t& thick_params=_deviceSettings->getThickParams();
		const float norm_val=thick_params.thick*0.01f;

		painter.fillRect(QRectF(curr_x, curr_y_b , next_x - curr_x, curr_height),_osc_background_color);

		if(thick_params.thick_lim_relative)
		{
			min_val = norm_val * (1.0f - thick_params.thick_lim_rel_neg * 0.001f);
			max_val = norm_val * (1.0f + thick_params.thick_lim_rel_pos * 0.001f);
		}
		else
		{
			min_val = norm_val - thick_params.thick_lim_neg * 0.01f;
			max_val = norm_val + thick_params.thick_lim_pos * 0.01f;
		}

		float curr_range = max_val * (1 + thick_range_coefficient);
		const float plot_step_thick_y = (curr_height - 1) / curr_range;
		if(elem_info->filled && (sum_thick.min_thick <= sum_thick.max_thick))	// условие того, что толщина определена
		{
			float curr_thick = sum_thick.min_thick;
			if((sum_thick.max_thick > max_val) && (sum_thick.min_thick > min_val))
				curr_thick = sum_thick.max_thick;

			if(sum_thick.min_thick < min_val)
				painter.fillRect(QRectF(curr_x, curr_y_b , next_x - curr_x, /*(curr_thick - por_neg) * plot_step_thick_y))*/curr_height),_error_color);
			else if(sum_thick.max_thick > max_val)
				painter.fillRect(QRectF(curr_x, curr_y_b , next_x - curr_x, (/*base_y +*/ (curr_thick - por_neg) * plot_step_thick_y)),_thick_color);
			else
				painter.fillRect(QRectF(curr_x, curr_y_b , next_x - curr_x, (/*base_y +*/ (curr_thick - por_neg) * plot_step_thick_y)), _sufficient_condition_color );
		}
	};

#endif//PlotMnemoThickElement lambda


	/*PlotMnemoThickLine lambda отвечает за отрисовку линии толщины, за уровень принимается минимальная толщина*/
#if 1
	auto _PlotMnemoThickLine=[=](QPainter& painter,
		const Element_Info* elem_info_prev,
		const Element_Info* elem_info_curr,
		const float curr_x,
		const float next_x,
		const int curr_y_b,
		const int curr_height,
		const float thick_range_coefficient
		)
	{
		const thick_values_t &sum_thick_prev = elem_info_prev->sum_defect.sum_thick;
		const thick_values_t &sum_thick_curr = elem_info_curr->sum_defect.sum_thick;
		const par_thick_t& thick_params=_deviceSettings->getThickParams();
		const float norm_val=thick_params.thick*0.01f;
		float min_val = 0;
		float max_val = 0;
		float por_neg = 0.0;

		if(thick_params.thick_lim_relative)
		{
			min_val = norm_val * (1.0f - thick_params.thick_lim_rel_neg * 0.001f);
			max_val = norm_val * (1.0f + thick_params.thick_lim_rel_pos * 0.001f);
		}
		else
		{
			min_val = norm_val - thick_params.thick_lim_neg * 0.01f;
			max_val = norm_val + thick_params.thick_lim_pos * 0.01f;
		}

		float curr_range = max_val * (1 + thick_range_coefficient);
		const float plot_step_thick_y = (curr_height - 1) / curr_range;
		painter.save();
		//QVector<qreal> point_paretten;
		//point_paretten << 3 << 10;
		QPen pen_dash;
		//pen_dash.setColor(p_OscProp->SufficientConditins);
		//pen_dash.setDashPattern(point_paretten);
		pen_dash.setWidthF(1.5);
		painter.setPen(pen_dash);
		const float base_y = curr_y_b;//верхняя граница отрисовки
		float prev_y=0.0;
		float curr_y=0.0;
		if((sum_thick_curr.max_thick > max_val) && (sum_thick_curr.min_thick > min_val))
			curr_y = base_y + (sum_thick_curr.max_thick - por_neg) * plot_step_thick_y;
		else
			curr_y = base_y + (sum_thick_curr.min_thick - por_neg) * plot_step_thick_y;

		if((sum_thick_prev.max_thick > max_val) && (sum_thick_prev.min_thick > min_val))
			prev_y = base_y + (sum_thick_prev.max_thick - por_neg) * plot_step_thick_y;
		else
			prev_y = base_y + (sum_thick_prev.min_thick - por_neg) * plot_step_thick_y;
		QLine line;
		line.setLine(curr_x, prev_y, next_x, curr_y);
		painter.drawLine(line);
		painter.restore();
	};
#endif//PlotMnemoThickLine lambda

	/*_PlotMnemoElem lambda заполняет уровни суммой дефектов верх-середина-низ;продольный & поперечный - разный цвет и разный "вес" в зависимости от flaw_size*/
#if 1
	auto PlotSingleMnemoElem=[=]( QPainter& painter,
		const Element_Info* elem_info,
		const int layer,
		const float curr_x,
		const float next_x,
		const int curr_y_b,
		const int curr_height,
		const float flaw_height_coeff)
	{
		//painter.save();
		painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height),_mnemo_background_color );

		const defect_dimentions_t& def_dim=elem_info->sum_defect.sum_defect_layer.at(layer);
		if((def_dim.flaw_poper == 0)&&(def_dim.flaw_plos == 0))
			return;
		const int margin=curr_height/8;
		const int mnemo_elem_height=curr_height-margin*2;
		float flaw_plos_weigth=def_dim.flaw_plos*1.0/(def_dim.flaw_plos+def_dim.flaw_poper);

		float flaw_poper_weigth=def_dim.flaw_poper*1.0/(def_dim.flaw_plos+def_dim.flaw_poper);
		painter.save();
		painter.translate(curr_x,curr_y_b);
		painter.fillRect(QRectF(0, margin , next_x - curr_x, mnemo_elem_height*flaw_plos_weigth),_flaw_prod_color);
		painter.translate(0,mnemo_elem_height*flaw_plos_weigth+margin);
		painter.fillRect(QRectF(0, 0, next_x - curr_x, mnemo_elem_height*flaw_poper_weigth), _flaw_poper_color );
	//	qDebug()<<"p_def_dim->flaw_plos =" << def_dim.flaw_plos<<" p_def_dim->flaw_poper =" << def_dim.flaw_poper;
		painter.restore();
	};


	auto _PlotMnemoElem=[=]( QPainter& painter,
							const Element_Info* elem_info,
							const float curr_x,
							const float next_x,
							const std::vector<int>& row_b,
							const std::vector<int>& row_height,
							const float flaw_height_coeff)
	{
		quint8 mnemo_flags = _deviceSettings->getUsedLayers();
		quint8 curr_mnemo_row = 0;
				quint8 curr_mnemo_layer = 0;


				if(mnemo_flags & USED_LAYER_0)
				{
					PlotSingleMnemoElem(	painter, 
						elem_info,
						curr_mnemo_layer,
						curr_x,
						next_x,
						row_b[curr_mnemo_row],
						row_height[curr_mnemo_row],
						flaw_height_coeff);
					curr_mnemo_row++;
				}
				curr_mnemo_layer++;

				if(mnemo_flags & USED_LAYER_1)
				{
					PlotSingleMnemoElem(	painter, 
						elem_info,
						curr_mnemo_layer,
						curr_x,
						next_x,
						row_b[curr_mnemo_row],
						row_height[curr_mnemo_row],
						flaw_height_coeff);
					curr_mnemo_row++;
				}
				curr_mnemo_layer++;

				if(mnemo_flags & USED_LAYER_2)
					PlotSingleMnemoElem(	painter, 
					elem_info,
					curr_mnemo_layer,
					curr_x,
					next_x,
					row_b[curr_mnemo_row],
					row_height[curr_mnemo_row],
					flaw_height_coeff);

	};
#endif//_PlotMnemoElem lambda
	/*SetNumMnemoRows lambda в зависимости от установленных флагов определяет количество строк в мнемосхеме*/
#if 1
auto SetNumMnemoRows=[=](quint8& num_mnemo_rows,quint8& num_thick_row){
quint8 mnemo_flags = _deviceSettings->getUsedLayers();



	if(mnemo_flags & USED_LAYER_0)
		num_mnemo_rows++;
	if(mnemo_flags & USED_LAYER_1)
		num_mnemo_rows++;
	if(mnemo_flags & USED_LAYER_2)
		num_mnemo_rows++;
	if(mnemo_flags & USED_LAYER_THICK)
	{
		num_thick_row = num_mnemo_rows;
		num_mnemo_rows++;
	}
	};
#endif//SetNumMnemoRows


	QPixmap pixmap(w,h);
	pixmap.fill(Qt::white);
	QPainter painter;
	painter.begin(&pixmap);
	painter.drawRect(1,1,w-2,h-2);
	//painter.save();
	painter.translate(2,2);
	quint8 num_mnemo_rows = 0;
	quint8 thick_row_num = 0;
	const float thick_range_coefficient=0.2f;
	float pixmap_width=(float)(w-2);
	const float plot_step_x=3.0;
	const float left_tab=0.0f;
	SetNumMnemoRows(num_mnemo_rows,thick_row_num);
	const float pix_h_step = static_cast<float>(h+1)/num_mnemo_rows;
	const int MAX_FLAW_SIZE=14;
	const float flaw_height_coeff = (pix_h_step - 1.0f) / MAX_FLAW_SIZE;
	std::vector<int> row_b(num_mnemo_rows+1);
	std::vector<int> row_height(num_mnemo_rows);
		
	SetupMnemoRowDim(row_b,row_height,num_mnemo_rows,pix_h_step);
	PlotMnemoRowsLine(painter,row_b,num_mnemo_rows);
	float curr_x = left_tab;
	float next_x = left_tab + plot_step_x/2;
	if(elem_list.count()>0)
	{
		//отрисовка 1 элемента персонально
		PlotMnemoThickElement(painter,elem_list.at(_beg_index-1),curr_x,next_x,row_b.at(thick_row_num)+1,row_height.at(thick_row_num)-1-row_height.size(),thick_range_coefficient);
		_PlotMnemoElem(painter,elem_list.at(_beg_index-1),curr_x,next_x,row_b,row_height,flaw_height_coeff);
		curr_x = next_x;
		int elements_count=0;
	//	int beg=1;
		elements_count=elem_list.count();
		int requested_size=pixmap_width/plot_step_x+1;

		if(requested_size<elements_count)
		{
			_beg_index=elements_count-requested_size;
		}
		for (int i=_beg_index;i<elements_count;i++)
		{
			next_x += plot_step_x;

			if(elem_list.at(i)->filled)
			{
				_PlotMnemoElem(painter,elem_list[i],curr_x,next_x,row_b,row_height,flaw_height_coeff);
				if(thick_row_num>0)
				{

					PlotMnemoThickElement(painter,elem_list.at(i),curr_x,next_x,row_b.at(thick_row_num)+1,row_height.at(thick_row_num)-1-row_height.size(),thick_range_coefficient);
					_PlotMnemoThickLine(painter,elem_list[i-1],elem_list[i],curr_x,next_x,row_b.at(thick_row_num),row_height.at(thick_row_num),thick_range_coefficient);
				}
			}

			curr_x=next_x;

		}
	}
	if(thick_row_num>0)
	{
		PlotThickLevel(painter,row_b.at(thick_row_num),row_height.at(thick_row_num),thick_range_coefficient);
	}
	painter.end();
	//painter.restore();
	return pixmap;
}
DrawCoordRow::DrawCoordRow(DeviceSettings* dev_settings):DrawStrategy(dev_settings)
{
}
 QImage DrawCoordRow::Draw(int w,int h,const QList<Element_Info*>& list)
 {
	 return QImage();
 }
QPixmap DrawCoordRow::DrawPixmap(int w,int h, const QList<Element_Info*>& elem_list)
{
	/* PrintCoordValueTxt lambda отображает координату value в заданном месте*/
#if 1
	auto PrintCoordValueTxt=[=](QPainter& painter,const float curr_x,const float pixmap_height,const int value)
	{
		QRectF rectTxt(curr_x+2,pixmap_height/50,txtWidth,pixmap_height-pixmap_height/50);
		QString strValue=QString::number(value,10);
		painter.drawText(rectTxt,Qt::AlignLeft,strValue);

	};
#endif
	QPixmap pixmap(w,h);
	pixmap.fill(Qt::white);
	QPainter painter(&pixmap);
	painter.drawRect(1,1,w-2,h-2);
	painter.translate(3,2);
	const float pixmap_width=(float)w;
	const float pixmap_height=(float)h;
	const float plot_step_x=3.0;
	const float left_tab=0.0f;
	float curr_x = left_tab;
	
	if(elem_list.count()>0)
	{
		
		int elements_count=0;
		int beg=0;
		elements_count=elem_list.count();
		int requested_size=pixmap_width/plot_step_x+1;

		if(requested_size<elements_count)
		{
			beg=elements_count-requested_size;
		}
		for (int i=beg;i<elements_count;i++)
		{
			

			if(elem_list.at(i)->filled)
			{
				
						
						if(elem_list.at(i)->coord%10==0)
						{
							QLineF line( curr_x,  pixmap_height/4, curr_x,  pixmap_height);
							painter.drawLine(line);
							if((curr_x+txtWidth)<pixmap_width)
							PrintCoordValueTxt(painter,curr_x,pixmap_height,elem_list.at(i)->coord);
						}
						else if(elem_list.at(i)->coord%5==0)
						{
							QLineF line( curr_x,  4*pixmap_height/7, curr_x,  pixmap_height);
							painter.drawLine(line);
						}
						else
						{
							QLineF line( curr_x,  3*pixmap_height/4, curr_x,  pixmap_height);
							painter.drawLine(line);
						}
			}

			curr_x+=plot_step_x;

		}
	}

	return pixmap;
}

 QImage DrawBScanRow::Draw(int w,int h,const QList<Element_Info*>& list)
 {
	 return QImage();
 }
QPixmap DrawBScanRow::DrawPixmap(int w,int h, const QList<Element_Info*>& elem_list)
{
	QPixmap pixmap(w,h);
	pixmap.fill(Qt::magenta);
	return pixmap;
}