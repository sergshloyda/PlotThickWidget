#include "griditem.h"
#include "qapplication.h"
#include <cmath>
#include "qdebug.h"
GridItem::GridItem(quint8 numChan,QGraphicsObject *parent)
	: QGraphicsObject(parent),
	_font_size(16),
	_x_b(0.0),
	_y_b(0.0),
	_x_sign_step(48),
	_y_sign_step(32),
	_numChan(numChan)
{
	_deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
	_gridColor=_deviceSettings->getOscColor("GRID_LINE_COLOR");
	_textColor=_deviceSettings->getOscColor("TEXT_COLOR");
	_plot_color=_deviceSettings->getOscColor("PLOT_LINE_COLOR");
	 curr_osc_par=_deviceSettings->getDeviceStruct().view_par.osc_par;
	 cn_info_par=_deviceSettings->getDeviceStruct().contr_par.trk_par.cn_list.cn_info[_numChan];
	 curr_view_cn_par=_deviceSettings->getDeviceStruct().view_par.view_info[_numChan];
	 log_5=std::log10f(5.0);
	 log_2=std::log10f(2.0);

}

GridItem::~GridItem()
{

}
QRectF GridItem::boundingRect() const
{
	return scene()->sceneRect();
	//	return _parent_scene->sceneRect();
}

void GridItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
 QRectF gridRect=boundingRect().adjusted(x_margin,y_margin,-x_margin,-y_margin);

	/*
	auto PrintVertCoordValue=[=](QPainter* painter,const float curr_x,const float curr_y,const float txtWidth,const float txtHeight,const int value)
	*/
#if 1
	auto PrintVertCoordValue=[=](QPainter* painter,const float curr_x,const float curr_y,const float txtWidth,const float txtHeight,const float font_size,const int value)
	{
		const float vert_gap=5.0f;
		const float horiz_gap=3.0f;
		painter->save();
		QPen pen2( _textColor);
		painter->setPen(pen2);
		QFont curr_font = painter->font();
		curr_font.setPixelSize(font_size);
		painter->setFont(curr_font);
		QRectF rectTxt(curr_x-txtWidth,curr_y-txtHeight+vert_gap,txtWidth-horiz_gap,txtHeight);
		QString strValue=QString::number(value,10);
		painter->drawText(rectTxt,Qt::AlignRight|Qt::AlignBottom,strValue);
		painter->restore();
	};
#endif
	/*auto PrintHorizCoordValue=[=](QPainter* painter,const float curr_x,const float curr_y,const float txtWidth,const float txtHeight,const int value) 
	PrintCoordValue lambda отображает координату value в заданном месте*/
#if 1
	auto PrintHorizCoordValue=[=](QPainter* painter,const float curr_x,const float curr_y,const float txtWidth,const float txtHeight,const float font_size,const int value)
	{
		painter->save();
		QPen pen2( _textColor);
		painter->setPen(pen2);
		QFont curr_font = painter->font();
		curr_font.setPixelSize(font_size);
		painter->setFont(curr_font);
		QRectF rectTxt(curr_x-txtWidth/2,curr_y,txtWidth,txtHeight);
		QString strValue=QString::number(value,10);
		painter->drawText(rectTxt,Qt::AlignHCenter|Qt::AlignVCenter,strValue);
		painter->restore();

	};
#endif
	/*auto DrawRowLines=[=](QPainter* painter,const QRectF& grid_rect,const int row_count)*/
#if 1
	auto DrawRowLines=[=](QPainter* painter,const QRectF& grid_rect,const int row_count)
	{

		
		const float height=grid_rect.height();
	    const float coeff = painter->fontMetrics().boundingRect("0").height()/16.0f;
		float curr_font_size=_font_size;
		curr_font_size *= coeff;
		QPen pen1(_gridColor);
	
		pen1.setWidth(1);

		painter->save();
		painter->setPen(pen1);
	
		const float y_val_step = static_cast<float>(MAX_FLOAT_OSC  / row_count) ;	//100.0f //255.0f
		float y_val = 0.5f;
		float y_pos=grid_rect.bottom();
		const float step_y=grid_rect.height()/row_count;
		for(int i=0;i<=row_count;i++)
		{
			
			painter->setPen(pen1);
			painter->drawLine(grid_rect.left(),y_pos,grid_rect.right(),y_pos);
			PrintVertCoordValue(painter,grid_rect.left(),y_pos,x_margin,y_margin,curr_font_size,static_cast<int>(y_val));
			y_val += y_val_step;
			y_pos -=  step_y;

		}
		painter->restore();
	};
#endif
	/*	auto DrawColumnLines=[=](QPainter* painter,const QRectF& grid_rect, DeviceSettings* deviceSettings,const int colunm_count)*/
#if 1
	auto DrawColumnLines=[=](QPainter* painter,const QRectF& grid_rect, DeviceSettings* deviceSettings,const int colunm_count)
	{
	//const par_osc_t& curr_osc_par=deviceSettings->getDeviceStruct().view_par.osc_par;
	painter->save();
	const float FullOscLen=(curr_osc_par.curr_stp_r + 1) * LEN_OSC * STEP_KOEF;
	float x_val = curr_osc_par.curr_beg_r/TEN_F; 
	const float width=grid_rect.width();
	const float height=grid_rect.height();
	const float x_step = width /colunm_count;
    const float coeff = painter->fontMetrics().boundingRect("0").height()/16.0f;
	float curr_font_size=_font_size;
	float curr_x_sign_step=_x_sign_step;
	float curr_y_sign_step=_y_sign_step;
	curr_x_sign_step *= coeff;
	curr_y_sign_step *= coeff;
	curr_font_size *= coeff;

	_y_b=y_margin;
	_x_b=x_margin;
	QPen pen1(_gridColor);
	pen1.setWidth(1);
	painter->setPen(pen1);




	float x_val_per_pix = FullOscLen / width ;			// приращение, приходящееся на 1 пиксель

	if(!curr_osc_par.rej_osc)
		x_val_per_pix = 0.025f  * LEN_OSC / width ;
    //const cn_info_t &cn_info_par=deviceSettings->getDeviceStruct().contr_par.trk_par.cn_list.cn_info[_numChan];
	const float alpha = cn_info_par.probe_par.alpha*3.141592653f/(180.0f*COEF_ALPHA);
	//const view_cn_info_t &curr_view_cn_par=deviceSettings->getDeviceStruct().view_par.view_info[_numChan];
	switch(curr_view_cn_par.axis_mode.axis_x_mode)
	{
	case AXIS_MODE_MKS:
		if((cn_info_par.rej != TD_TOL) && (cn_info_par.rej != TD_TOL_REZ))
			x_val = x_val - 0.002f * cn_info_par.probe_par.t_pr;
		break;
				
	case AXIS_MODE_Y_MM:
		{
			float curr_cos_alpha = cos(alpha);
			if(curr_cos_alpha == 0.0f)
				return;
				
			x_val_per_pix = curr_cos_alpha * 0.5f * x_val_per_pix  * 0.001f * cn_info_par.probe_par.cc;	

			if((cn_info_par.rej != TD_TOL) && (cn_info_par.rej != TD_TOL_REZ))
				x_val = curr_cos_alpha * (0.5f * x_val - 0.001f *cn_info_par.probe_par.t_pr)  * 0.001f * cn_info_par.probe_par.cc;
			else
				x_val = 0.5f * x_val  * 0.001f * cn_info_par.probe_par.cc;

//				is_thick_measure = (curr_dop_par.thick.on_thick == 1);
		}
		break;
				
	case AXIS_MODE_X_MM:
		{
			float curr_sin_alpha = sin(alpha);
			if(curr_sin_alpha == 0.0f)
				return;
				
			x_val_per_pix = curr_sin_alpha * 0.5f * x_val_per_pix  * 0.001f * cn_info_par.probe_par.cc;

			if((cn_info_par.rej != TD_TOL) && (cn_info_par.rej != TD_TOL_REZ))
				x_val = curr_sin_alpha * (0.5f * x_val - 0.001f *cn_info_par.probe_par.t_pr)  * 0.001f * cn_info_par.probe_par.cc; // - curr_cn_par.strela * 0.1f; ???
			else
				x_val = 0.0f;
		}
		break;
	}

	// определяем, сколько элементов приходится на 1 клетку
		
	double grid_elem_count = x_val_per_pix * x_step;
	double grid_elem_pow = std::log10(grid_elem_count);
		
		
	QLine line;
		
	if(grid_elem_pow > 0)	// т.е. более 1 элемента на клетку
	{
		int dec_elem_pow = (int)grid_elem_pow;
		int value_incrim = 1;
			
		if( (grid_elem_pow - dec_elem_pow) > log_5 )	// > (log10(5)) т.е. умножаем ещё на 5
			value_incrim *= 5;
		else if( (grid_elem_pow - dec_elem_pow) > log_2 )	// т.е. умножаем ещё на 2
			value_incrim *= 2;
			
		for(int i = 0; i < dec_elem_pow; i++)
			value_incrim *= 10;					// итого получаем, на сколько смещаемся в элементах
			
			
		float x_val_step = value_incrim / x_val_per_pix;		// пикселей в приращении 
			
		{
			
			int x_curr_val;
			bool x_val_not_pos=x_val <= 0;
			bool x_val_equal_val_increm=(x_val-value_incrim)<0.00001;
	/*		if(x_val > 0)
				x_curr_val = (int)(x_val / value_incrim) + 1;
			else
				x_curr_val = (int)(x_val / value_incrim);*/
			if(x_val_not_pos||x_val_equal_val_increm)
				x_curr_val = (int)(x_val / value_incrim);
			else
				x_curr_val = (int)(x_val / value_incrim) + 1;
			
			x_curr_val *= value_incrim;
			

			float x_curr_pos = x_curr_val - x_val;		// от начала до первого значения в единицах 
			x_curr_pos /= x_val_per_pix;				// в пикселях
			
			x_curr_pos += _x_b;

			float temp_x_pos = curr_x_sign_step;
			
			while(x_curr_pos < (_x_b + width))
			{
				if(x_curr_val >= 0)
				{
					if(temp_x_pos >= curr_x_sign_step)
					{
					
						PrintHorizCoordValue(painter,x_curr_pos,height+y_margin,y_margin,x_margin,curr_font_size,x_curr_val);
						line.setLine( x_curr_pos, _y_b, x_curr_pos, _y_b + height + 5);
						painter->drawLine(line);

						temp_x_pos = 0;
					}
					else
					{
						line.setLine( x_curr_pos, _y_b, x_curr_pos, _y_b + height);
						painter->drawLine(line);
					}
					
					temp_x_pos += x_val_step;
				}
				else
				{
						line.setLine( x_curr_pos, _y_b, x_curr_pos, _y_b + height);
						painter->drawLine(line);
				}
				
				x_curr_val += value_incrim;
				x_curr_pos += x_val_step;	
			}


		}


	}
	else if(grid_elem_pow > -1)		// менее 1 элемента на клетку, но больше 0.1 части, а если ещё меньше - не отрисовываем
	{
		// grid_elem_pow от -1 до 0

		float value_incrim = 0.1f;
			
		if( (grid_elem_pow + 1) > 0.699 )	// > (log10(5)) т.е. умножаем ещё на 5
			value_incrim *= 5;
		else if( (grid_elem_pow + 1) > 0.301 )	// т.е. умножаем ещё на 2
			value_incrim *= 2;
			
		float x_val_step = value_incrim / x_val_per_pix;		// пикселей в приращении 
			


	
		{

			float x_curr_val = 0;
			
			if(x_val > 0)
				x_curr_val = (int)(x_val / value_incrim) + 1;
			else
				x_curr_val = (int)(x_val / value_incrim);
			
			x_curr_val *= value_incrim;
			
			
			float x_curr_pos = x_curr_val - x_val;		// от начала до первого значения в единицах 
			x_curr_pos /= x_val_per_pix;				// в пикселях
			x_curr_pos += _x_b;	
			
			float temp_x_pos = curr_x_sign_step;	
				
			while(x_curr_pos < (_x_b + width))
			{
				if(x_curr_val >= 0)
				{
					if(temp_x_pos >= curr_x_sign_step)
					{
						/*painter.setPen(pen2);
						OutFrameText(painter, QString::number(x_curr_val, 'f', 1), frame_width/2 + (int)x_curr_pos,  pixmap_height, frame_width, frame_width);*/
						painter->setPen(pen1);

						line.setLine( x_curr_pos, _y_b, x_curr_pos, _y_b + height + 5);
						painter->drawLine(line);

						temp_x_pos = 0;
					}
					else
					{
						line.setLine( x_curr_pos, _y_b, x_curr_pos, _y_b + height);
						painter->drawLine(line);
					}
					temp_x_pos += x_val_step;
				}
				else
				{
					line.setLine( x_curr_pos, _y_b, x_curr_pos, _y_b + height);
					painter->drawLine(line);
				}
				
				x_curr_val += value_incrim;
				x_curr_pos += x_val_step;	
			}

		}

	}
	painter->restore();
	};
#endif
/*auto DrawBorderPlot=[](QPainter* painter,const QRectF& plotterBorderRect)*/
#if 1
	auto DrawBorderPlot=[](QPainter* painter,const QRectF& plotterBorderRect)
	{
		QPen penBorder(Qt::black);
		penBorder.setWidthF(2.5);
		painter->setPen(penBorder);
		painter->drawRect(plotterBorderRect);
	};
#endif

/*auto DrawPlot=[=](QPainter* painter)*/
#if 1
	auto DrawPlot=[=](QPainter* painter)
	{
		painter->save();
		painter->setRenderHint(QPainter::Antialiasing, false);
		QPen penPlot(_plot_color);
		penPlot.setWidthF(2.5);
		painter->setPen(penPlot);
		painter->drawPolyline(_osc_line);
		
		painter->restore();
	};
#endif
	DrawRowLines(painter,gridRect,GridItem::grid_row_count);
	DrawColumnLines(painter,gridRect,_deviceSettings,GridItem::grid_column_count);
	DrawPlot(painter);
	DrawBorderPlot(painter,gridRect);
	

	 
//polyline.append(QPointF(10, 20)); // add your points
//polyline.append(QPointF(20,30));

	
      Q_UNUSED(option);
      Q_UNUSED(widget);
}

void GridItem::refresh_osc(const QByteArray& osc_array)
{
	/*
	auto deserialize_from_QByteArray=[=](QPolygonF& osc_line,const QRectF& plotRect)
	*/
#if 1
auto deserialize_from_QByteArray=[=](QPolygonF& osc_line,const QRectF& plotRect)
{
	QDataStream stream(osc_array);
    stream.setVersion(QDataStream::Qt_4_5);
	int size=0;
	stream>>size;
	Q_ASSERT(size>0);
	const float x_step = plotRect.width() /size;
	const float y_step=plotRect.height()/255.0;
	const float bottom_grid=plotRect.bottom();
	float x_pos=plotRect.left();
	for (int i=0;i<size;i++)
	{
		quint8 val;
		stream >> val;
		x_pos+=x_step;
		osc_line.append(QPointF(x_pos, bottom_grid-val*y_step));
	}
};
#endif
	QRectF gridRect=boundingRect().adjusted(x_margin,y_margin,-x_margin,-y_margin);
	_osc_line.clear();
	deserialize_from_QByteArray(_osc_line,gridRect);
	update();
}