#include "DrawDefectRow.h"
#include "qimage.h"
#include "qpainter.h"
DrawDefectRow::DrawDefectRow(quint8 num_chan,DeviceSettings* device_settings):DrawStrategy(device_settings),
	_num_chan(num_chan),_beg_index(1),_prev_filled(false),_prev_strob_ak_level(0) 
{
	setColors();
	
	
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
			QColor tmp_Color=_deviceSettings->getStrobColor(i);
			tmp_Color.getHsv(&hue, &strat, &value);

			SubStrobsColor[i][0] = QColor::fromHsv(hue, 0.4f*strat, 0.5f*(255-value)+value);
			SubStrobsColor[i][1] = QColor::fromHsv(hue, 0.6f*strat, 0.25f*(255-value)+value);
			SubStrobsColor[i][2] =  tmp_Color;
		}
		else
			SubStrobsColor[i][0] =_deviceSettings->getStrobColor(i);
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
				strob_fill_color=_deviceSettings->getStrobColor(pos->first);
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
				PlotStrobPorLevel(painter, pen0, _deviceSettings->getStrobsColor().at(i), pen2, line_base.translated(0, -strb_par[i].por*plot_step_y), offset);

		}
	}
	painter.restore();
	painter.end();

	return img;
}

QPixmap DrawDefectRow::DrawPixmap(int w,int h,const QList<Element_Info*>& list)
{

#if 0



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

			// по уровням 



		_timer.start();
	setColors();
	
		if (_timer.isValid())
		{
		//	qDebug() << "gui time = " << _timer.elapsed()<<" elements_count:"<<list.count();
			_timer.invalidate();
		}
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
			DefectElement* def_elem_0=static_cast<DefectElement*>(list.at(_beg_index-1)->chan_info_array.at(_num_chan));
			if(def_elem_0->filled)
		{
			_prev_strob_ak_level = def_elem_0->strobs[NUM_STROB_AK].strob_data.ampl;
			_prev_filled = true;
		}
		PlotDefectElement(painter,def_elem_0,strb_par,strb_chan_info,curr_x,next_x,pixmap_height,plot_step_y);

		elements_count=list.count();
		if(requested_size<elements_count)
		{
			_beg_index=elements_count-requested_size;
		}

	

		for(int j = _beg_index; j < elements_count; j++)
		{
			bool thick_filled = false;
			DefectElement* def_elem=static_cast<DefectElement*>(list.at(j)->chan_info_array.at(_num_chan));
			PlotDefectElement(painter,def_elem,strb_par,strb_chan_info,curr_x,next_x,pixmap_height,plot_step_y);
			curr_x = next_x;
			next_x = curr_x + plot_step_x;

			_prev_strob_ak_level = def_elem->strobs[NUM_STROB_AK].strob_data.ampl;
			_prev_filled = true;

		}

	}

	for(quint8 i = 0; i < NUM_STRBS; i++)
	{
		if(strb_par[i].on_strb)	// наличие многоуровневого строба не важно, важна абс. амплитуда строба
		{
			if(strb_chan_info[i].on_extra_por)
			{
				PlotStrobPorLevel(painter, pen1, _sub_strobs_color[i][0], pen2, line_base.translated(0, -strb_par[i].por*plot_step_y), offset);
				//PorLabel(painter,strb_par[i].por);
				for(quint8 j = 0; j < NUM_STRBS_EXTRA; j++)
				{
					PlotStrobPorLevel(painter, pen1, _sub_strobs_color[i][j+1], pen2, line_base.translated(0, -strb_chan_info[i].extra_por[j]*plot_step_y), offset);
					//	PorLabel(painter,strb_chan_info[i].extra_por[j]);
				}
			}
			else
				PlotStrobPorLevel(painter, pen0, _deviceSettings->getStrobColor(i), pen2, line_base.translated(0, -strb_par[i].por*plot_step_y), offset);
		}
	}
	painter.restore();
	painter.end();
	return pixmap;
}

void DrawDefectRow::PlotDefectElement(QPainter& painter,const DefectElement* def_elem,  const par_strb_t *strb_par,const par_strb_info_t *strb_chan_info,float curr_x,const float next_x,const float pixmap_height,const float plot_step_y)
{
			if(!def_elem->filled)
		return;
			// отрисовка включенных стробов в порядке возрастания амплитуды, за исключением сигнала АК, который рисуется линией на заднем плане (?) + закраской на переднем
			
		const float base_y = pixmap_height;
		
		// отрисовка стробов в порядке убывания амплитуды (в виде прямоугольников высотой strob_data.ampl)

		bool any_def = false;
		QColor strob_fill_color;
		QRectF rect;

		std::vector<std::pair<quint8,sum_strob_info_t>> sorted_strobs;
		quint8 index_strob=1;
		std::vector<sum_strob_info_t>::const_iterator it_begin=def_elem->strobs.begin()+1;//сортировка начиная со 2 строба
		

		for(auto elem=it_begin;elem!=def_elem->strobs.end();++elem)
		{
			sorted_strobs.push_back(std::make_pair(index_strob++,*elem));
		}
		std::sort(sorted_strobs.begin(),sorted_strobs.end(),
			[](const std::pair<quint8, sum_strob_info_t>& a,const std::pair<quint8, sum_strob_info_t>& b) 
		{return a.second.strob_data.ampl > b.second.strob_data.ampl;});/**/


			for( auto pos=sorted_strobs.begin();pos!=sorted_strobs.end();++pos)
			{
				//	qDebug()<<"Index:"<<pos->first<<" Ampl:"<< pos->second.strob_data.ampl;
				quint8 strob=pos->first;
				strob_fill_color=_sufficient_condition_color;
				bool not_setted=true;
				if(strb_chan_info[strob].on_extra_por)
				{
					qint8 j = NUM_STRBS_EXTRA - 1;

					//спускаемся сверху вниз, как только обнаружим превышение над уровнем, выходим из цикла, окрашиваем амплитуду в цвет строба
					while((j >= 0) && not_setted)
					{
						if(def_elem->strobs[strob].strob_data.ampl > strb_chan_info[strob].extra_por[j])
						{
							strob_fill_color = _sub_strobs_color[strob][j+1];
							not_setted = false;
						}

						j--;
					}

					if(not_setted)//превышения экстра порогов нет,проверяем просто порог
					{
						if(def_elem->strobs[strob].strob_data.ampl > strb_par[strob].por)
						{
							strob_fill_color = _sub_strobs_color[strob][0];
							any_def = true;
							not_setted = false;
						}
					}
					else
						any_def = true;
				}
				else
				{
					if(def_elem->strobs[strob].strob_data.ampl > strb_par[strob].por)
					{
						strob_fill_color = _deviceSettings->getStrobColor(strob);
						any_def = true;
						not_setted = false;
					}
				}

				rect.setCoords(curr_x, base_y - pos->second.strob_data.ampl*plot_step_y, next_x, base_y);
				painter.fillRect(rect, strob_fill_color);

				if(not_setted)/*по амплитуде нет превышения ,обозначим ее уровень просто точкой*/
					painter.fillRect(QRect(QPoint(curr_x + (strob - 1),	rect.y() + 0.5f), QSize(2, 1)),_deviceSettings->getStrobColor(strob));
			}


		
	if(strb_par[NUM_STROB_AK].on_strb)//если проверяем наличие АК
	{

		bool ak_defect = def_elem->strobs[NUM_STROB_AK].strob_data.ampl < strb_par[NUM_STROB_AK].por;//амплитуда строба АК меньше порога,устанавливаем флаг отсутствия АК

		if(strb_chan_info[NUM_STROB_AK].on_extra_por && (def_elem->strobs[NUM_STROB_AK].strob_data.ampl < strb_chan_info[NUM_STROB_AK].extra_por[NUM_STRBS_EXTRA - 1]))
			//амплитуда меньше, чем самый высокий экстра порог
			ak_defect = true;


		float y_pos_a0 = base_y - def_elem->strobs[NUM_STROB_AK].strob_data.ampl*plot_step_y;//координата  -y- новой точки
	

		QPen line_pen(_deviceSettings->getStrobColor(NUM_STROB_AK));
		line_pen.setWidth(line_width);
		painter.setPen(line_pen);

		if(_prev_filled)//задана предыдущая точка
		{
			QLineF to_next_line( curr_x,  base_y - _prev_strob_ak_level*plot_step_y, curr_x,  y_pos_a0);//от предыдущей к новой
			painter.drawLine(to_next_line);
		}


		if(ak_defect)	// только в случае потери АК идёт прорисовка его амплитуды
		{
			
			QColor ak_color=_sub_strobs_color[0][0];
			if(strb_chan_info[NUM_STROB_AK].on_extra_por)
			{
				if(def_elem->strobs[NUM_STROB_AK].strob_data.ampl < strb_par[NUM_STROB_AK].por)
					ak_color = _sub_strobs_color[0][0];
				else
				{
					quint8 j = 0;
					bool not_setted = true;
					//подымаемся снизу вверх, как только НЕ обнаружим превышение над уровнем, выходим из цикла, окрашиваем амплитуду в цвет строба
					while((j < NUM_STRBS_EXTRA) && not_setted)
					{
						if(def_elem->strobs[NUM_STROB_AK].strob_data.ampl < strb_chan_info[NUM_STROB_AK].extra_por[j])
						{
							ak_color = _sub_strobs_color[0][j+1];
							not_setted = false;
						}
						j++;
					}
				}
			}

	if(any_def)	// прорисовка линии уровня АК
			{
				QPen line_pen(ak_color);
				line_pen.setWidth(AK_line_width);
				line_pen.setCapStyle(Qt::FlatCap);
				painter.setPen(line_pen);

				y_pos_a0 -= (AK_line_width - 1);


				QLineF ak_line( curr_x, y_pos_a0, next_x, y_pos_a0);
				painter.drawLine(ak_line);
			}
			else	// иначе закраска акустическим контактом
			{
				QRectF rect;
				rect.setCoords(curr_x, 0, next_x, y_pos_a0);//закрашивается вся область
				painter.fillRect(rect, ak_color);//вероятно и так будет отмечено позднее в PlotErrorSemiTrans??
			}
		}
		else
		{
			QLineF ak_line( curr_x, y_pos_a0, next_x, y_pos_a0);
			painter.drawLine(ak_line);
		}
	}

	PlotErrorFlags(painter,def_elem->error_flags,curr_x,next_x,0,pixmap_height);


}

void DrawDefectRow::PlotStrobPorLevel(QPainter & painter,QPen &pen,const QColor &col,QPen &back_pen,const QLineF &line,	int &offset)
	{
		pen.setColor(col);
		pen.setDashOffset(++offset);
		painter.setPen(pen);
		painter.drawLine(line);

		++offset;
		back_pen.setDashOffset(++offset);
		painter.setPen(back_pen);
		painter.drawLine(line);
	}


void DrawDefectRow::setColors()
{
	_sufficient_condition_color=_deviceSettings->getOscColor(QString("SUFFICIENT_CONDITION"));
	_ak_fill_color=_deviceSettings->getOscColor(QString("AK_FILL_COLOR"));
	_error_flag_incorrect_color=_deviceSettings->getIncorrectColor(QString("ERROR_FLAG_INCORRECT"));
	_error_flag_data_skip_color=_deviceSettings->getIncorrectColor(QString("ERROR_FLAG_DATA_SKIP"));
	_error_flag_no_ak_color=_deviceSettings->getIncorrectColor(QString("ERROR_FLAG_NO_AK"));
	_error_flag_lamination_color=_deviceSettings->getIncorrectColor(QString("ERROR_FLAG_LAMINATION"));
	_sub_strobs_color[0][0] = _ak_fill_color;
	_sub_strobs_color[0][0].setAlpha(180);
	const par_strb_info_t& strb_chan_info=_deviceSettings->getStrobInfo(_num_chan,NUM_STROB_AK);

	if(strb_chan_info.on_extra_por)
	{
		int hue;
		int strat;
		int value;
		_ak_fill_color.getHsv(&hue, &strat, &value);

		_sub_strobs_color[0][2] = QColor::fromHsv(hue, 0.4f*strat, 0.5f*(255-value)+value, 180);
		_sub_strobs_color[0][1] = QColor::fromHsv(hue, 0.6f*strat, 0.25f*(255-value)+value, 180);
	}
		
		for(quint8 num_strob = 1; num_strob < NUM_STRBS; num_strob++)		// первый строб пропускается
		{
		const par_strb_info_t&  strob_info = _deviceSettings->getStrobInfo(_num_chan,num_strob);
			if(strob_info.on_extra_por)
			{
				int hue;
				int strat;
				int value;
				QColor tmp_Color=_deviceSettings->getStrobColor(num_strob);
				tmp_Color.getHsv(&hue, &strat, &value);

				_sub_strobs_color[num_strob][0] = QColor::fromHsv(hue, 0.4f*strat, 0.5f*(255-value)+value);
				_sub_strobs_color[num_strob][1] = QColor::fromHsv(hue, 0.6f*strat, 0.25f*(255-value)+value);
				_sub_strobs_color[num_strob][2] =  tmp_Color;
			}
			else
				_sub_strobs_color[num_strob][0] =_deviceSettings->getStrobColor(num_strob);
		}



}

void DrawDefectRow::PlotErrorFlags(QPainter & painter,	const quint8 &defect_flag,const float curr_x,const float next_x,const int curr_y_b,const int curr_height)
{
	if((defect_flag & (ERROR_FLAG_NO_AK|ERROR_FLAG_LAMINATION)) == (ERROR_FLAG_NO_AK|ERROR_FLAG_LAMINATION))
	{
		// вверху - расслоение, ниже - потеря АК

		painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height/2), _error_flag_lamination_color );
		painter.fillRect(QRectF(curr_x, curr_y_b + curr_height/2, next_x - curr_x, curr_height/2), _error_flag_no_ak_color );
	}
	else
	{
		if(defect_flag & ERROR_FLAG_LAMINATION)
			painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height), _error_flag_lamination_color );

		if(defect_flag & ERROR_FLAG_NO_AK)
			painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height), _error_flag_no_ak_color );
	}




	if(defect_flag & ERROR_FLAG_DATA_SKIP)
		painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height), _error_flag_data_skip_color );
	if(defect_flag & ERROR_FLAG_INCORRECT)
		painter.fillRect(QRectF(curr_x, curr_y_b, next_x - curr_x, curr_height), _error_flag_incorrect_color );
}
