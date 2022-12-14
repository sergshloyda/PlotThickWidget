#include "OscillogramPlotterSetter.h"
#include <QPainter>
#include "qapplication.h"
#include "plottickwidget.h"
OscillogramPlotterSetter::OscillogramPlotterSetter(	QObject *refferece_obj, 
													OscillogramProperties *p_OscProp, 
													/*bool *tp_en_set_params,*/
													float *tp_sub_thick,
													amp_us_struct_t *tp_us_times/*, 
													bool * tp_plot_ogib, 
													quint8 * t_ogib*/) :

				PositionTesterPlotter(refferece_obj),
				AnyReceived(false),

				width(0),
				height(0),
				x_b(0.0f),
				y_b(0.0f),
				x_step(1.0f),
				y_step(1.0f),

				x_sign_step(48),
				y_sign_step(32),

				frame_width(36),

				font_size(16),


				ArrowDim(10),
				ArrowIndent(2),
				ArrowInterval(6),
				StrobSetHeight(6),

				VRChPtRadius(2),
				VRChPtCrossDim(30),
				VRChPtIndent(6),

				setted_koefficients(false),

				OscProp(p_OscProp),

				//p_en_set_params(tp_en_set_params),

				p_sub_thick(tp_sub_thick),
				p_us_times(tp_us_times),

				Old_ehogr_struct(),


				Old_osc_par(),
				Old_us_par(),
				Old_cn_info_par(),
				Old_view_cn_par(),

				Refference_osc_par(),
				Refference_us_par(),
				Refference_cn_info_par(),


/*				p_plot_ogib(tp_plot_ogib),
				ogib(t_ogib),
*/
//				beam_line(),


				curr_area(OscillogramPlotterSetter::Outside),

				_curr_strob(0),
				selected_vrch_point(0),

				vrch_relative_mode(false)			// ???
{

	connect(this, SIGNAL(SetStrobSelected(int)), refferece_obj, SLOT(SetStrobSelected(int)));
	connect(this, SIGNAL(BegOscIntermedChange(int)), refferece_obj, SLOT(BegOscIntermedChange(int)));
	connect(this, SIGNAL(BegOscFinalChange()), refferece_obj, SLOT(BegOscFinalChange()));
	connect(this, SIGNAL(EndOscIntermedChange(int)), refferece_obj, SLOT(EndOscIntermedChange(int)));
	connect(this, SIGNAL(EndOscFinalChange()), refferece_obj, SLOT(EndOscFinalChange()));

	connect(this, SIGNAL(SetStrobIntermedPos(int, int, int)), refferece_obj, SLOT(SetStrobIntermedPos(int, int, int)));
	connect(this, SIGNAL(SetStrobFinalPos()), refferece_obj, SLOT(SetStrobFinalPos()));
	connect(this, SIGNAL(SetStrobIntermedLeft(int, int, int)), refferece_obj, SLOT(SetStrobIntermedLeft(int, int, int)));
	connect(this, SIGNAL(SetStrobFinalLeft()), refferece_obj, SLOT(SetStrobFinalLeft()));
	connect(this, SIGNAL(SetStrobIntermedRight(int, int)), refferece_obj, SLOT(SetStrobIntermedRight(int, int)));
	connect(this, SIGNAL(SetStrobFinalRight()), refferece_obj, SLOT(SetStrobFinalRight()));


	connect(this, SIGNAL(SetStrobIntermedExtraPor2(int)), refferece_obj, SLOT(SetStrobIntermedExtraPor2(int)));
	connect(this, SIGNAL(SetStrobFinalExtraPor2()), refferece_obj, SLOT(SetStrobFinalExtraPor2()));
	connect(this, SIGNAL(SetStrobIntermedExtraPor3(int)), refferece_obj, SLOT(SetStrobIntermedExtraPor3(int)));
	connect(this, SIGNAL(SetStrobFinalExtraPor3()), refferece_obj, SLOT(SetStrobFinalExtraPor3()));



	connect(this, SIGNAL(SetBScanIntermedPos(int, int)), refferece_obj, SLOT(SetBScanIntermedPos(int, int)));
	connect(this, SIGNAL(SetBScanFinalPos()), refferece_obj, SLOT(SetBScanFinalPos()));
	connect(this, SIGNAL(SetBScanIntermedLeft(int, int)), refferece_obj, SLOT(SetBScanIntermedLeft(int, int)));
	connect(this, SIGNAL(SetBScanFinalLeft()), refferece_obj, SLOT(SetBScanFinalLeft()));
	connect(this, SIGNAL(SetBScanIntermedRight(int)), refferece_obj, SLOT(SetBScanIntermedRight(int)));
	connect(this, SIGNAL(SetBScanFinalRight()), refferece_obj, SLOT(SetBScanFinalRight()));




	connect(this, SIGNAL(SetVRChPointSelected(int)), refferece_obj, SLOT(SetVRChPointSelected(int)));
	connect(this, SIGNAL(SetVRChPointIntermedChange(int, int, int)), refferece_obj, SLOT(SetVRChPointIntermedChange(int, int, int)));
	connect(this, SIGNAL(SetVRChPointFinalPos()), refferece_obj, SLOT(SetVRChPointFinalPos()));

	connect(this, SIGNAL(OscAxisXChange()), refferece_obj, SLOT(OscAxisXChange()));
	connect(this, SIGNAL(OscAxisYChange()), refferece_obj, SLOT(OscAxisYChange()));

}

OscillogramPlotterSetter::OscillogramPlotterSetter(	 /*bool* tp_en_set_params,*/float*tp_sub_thick,amp_us_struct_t *tp_us_times, QObject *parent):
PositionTesterPlotter(parent),
				AnyReceived(false),

				width(0),
				height(0),
				x_b(0.0f),
				y_b(0.0f),
				x_step(1.0f),
				y_step(1.0f),

				x_sign_step(48),
				y_sign_step(32),

				frame_width(36),

				font_size(16),


				ArrowDim(10),
				ArrowIndent(2),
				ArrowInterval(6),
				StrobSetHeight(6),

				VRChPtRadius(2),
				VRChPtCrossDim(30),
				VRChPtIndent(6),

				setted_koefficients(false),
				

				//p_en_set_params(tp_en_set_params),

				p_sub_thick(tp_sub_thick),
				p_us_times(tp_us_times),
					Old_ehogr_struct(),


				Old_osc_par(),
				Old_us_par(),
				Old_cn_info_par(),
				Old_view_cn_par(),

				Refference_osc_par(),
				Refference_us_par(),
				Refference_cn_info_par(),/**/

			curr_area(OscillogramPlotterSetter::Outside),

				_curr_strob(0),
					selected_vrch_point(0),

				vrch_relative_mode(false)	
{
	
	OscProp=qApp->property("OscillogramProperties").value<OscillogramProperties*>();
	_main_widget=qobject_cast<PlotTickWidget*>(parent);
	


}
OscillogramPlotterSetter::~OscillogramPlotterSetter()
{
	//OscProp=nullptr;
}


void OscillogramPlotterSetter::SetCoefficients()			// запускать только 1 раз ???
{
	if(!MainPlotWidget || setted_koefficients)
		return;

	float koef = MainPlotWidget->fontMetrics().boundingRect("0").height()/16.0f;

	x_sign_step *= koef;
	y_sign_step *= koef;
	frame_width *= koef;
	font_size *= koef;
	ArrowDim *= koef;
	ArrowIndent *= koef;
	ArrowInterval *= koef;
	StrobSetHeight *= koef;
	VRChPtRadius *= koef;
	VRChPtCrossDim *= koef;
	VRChPtIndent *= koef;

	setted_koefficients = true;
}




QRect & OscillogramPlotterSetter::SetPlotRect(const QRect &fullRect)
{
	AbstactPlotter::SetPlotRect(fullRect);

	if(!NeedResize)
		return PosRect;

	width = pixmap_width - 2 * frame_width - 1;
	height = pixmap_height - 2 * frame_width - 1;

	if(width < 0)
		width = 0;

	if(height < 0)
		height = 0;

	x_b =  frame_width + 0.5;
	y_b =  frame_width + 0.5;
	x_step = static_cast<float>(width) / OscProp->column_number;
	y_step = static_cast<float>(height) / OscProp->row_number;

	PaintBackground();

	return PosRect;
}


void OscillogramPlotterSetter::ResetPlot()
{
	x_step = static_cast<float>(width) / OscProp->column_number;
	y_step = static_cast<float>(height) / OscProp->row_number;

	pixmap_width = 0; 
	pixmap_height = 0;

	UpdatePlot();
}


void OscillogramPlotterSetter::PaintBackground()
{
	if(pixmap_width != 0 && pixmap_height != 0)
	{
		if(AnyReceived)
			PlotRespond(Old_ehogr_struct, Old_osc_par, Old_us_par, Old_cn_info_par, Old_view_cn_par);
		else
		{
			QPainter painter(pixmap);

			if(!painter.isActive())
				return;

			painter.fillRect(0, 0, pixmap_width, pixmap_height, OscProp->BackgroundColor );

			DrawGrid(painter);
			PlotHorizontalSignature(painter, Old_osc_par, Old_cn_info_par, Old_view_cn_par);

			UpdatePlot();
		}
	}
}


void OscillogramPlotterSetter::DrawGrid(QPainter & painter)
{
	QPen pen1(OscProp->GridColor);
	pen1.setWidth(1);
	painter.setPen(pen1);

	QLine line;

	for(int i = 0; i < OscProp->row_number + 1; i++)
	{
		line.setLine( x_b, y_b + y_step * i, x_b + width,  y_b + y_step * i);
		painter.drawLine(line);
	}

	line.setLine( x_b, y_b, x_b, y_b + height);
	painter.drawLine(line);

	line.setLine( x_b + width, y_b, x_b + width, y_b + height);
	painter.drawLine(line);
}


void OscillogramPlotterSetter::PlotRespond(QPainter & painter, const osc_struct_t &curr_ehogr, const par_osc_t &curr_osc_par, const par_us_t &curr_us_par, const cn_info_t &cn_info_par, const view_cn_info_t &curr_view_cn_par)
{
	float koeff  = static_cast<float>(width) /((curr_osc_par.curr_stp_r + 1) * LEN_OSC * STEP_KOEF);//коэффициент пересчета пикселей в длину
	float OscBegin = curr_osc_par.curr_beg_r/TEN_F;



	if(curr_osc_par.rej_osc)
	{
		if(curr_us_par.rej != TD_B_SCAN)
		{
			for(quint8 ii = 0; ii < NUM_STRBS; ii++)						// 3ий строб не отрисовывается для резонансной толщинометрии ?
			{
				const par_strb_t &curr_strob = curr_us_par.strb[ii];

				bool on_strob = curr_strob.on_strb && !((curr_us_par.rej == TD_TOL_REZ) && (ii == REZ_NO_STROB));

				if(on_strob)
				{
					float s_begin= curr_strob.beg/TEN_F - OscBegin;
					float s_end= s_begin + curr_strob.len/TEN_F;
					float s_porog;
					
					if(cn_info_par.strb_info[ii].on_extra_por)
					{
						int hue;
						int strat;
						int value;
						OscProp->StrobsColor[ii].getHsv(&hue, &strat, &value);

						if(ii != 0)
						{/*стробы не АК  яркость падает при понижении уровня(самый яркий extra_por[1])*/
							s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.strb_info[ii].extra_por[1]) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, OscProp->StrobsColor[ii], false);

							QColor tmp_color = QColor::fromHsv(hue, 0.6f*strat, 0.25f*(255-value)+value);

							s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.strb_info[ii].sub_extra_por[1]) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, tmp_color, false, true);

							s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.strb_info[ii].extra_por[0]) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, tmp_color, false);


							tmp_color.setHsv(hue, 0.4f*strat, 0.5f*(255-value)+value);

							s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.strb_info[ii].sub_extra_por[0]) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, tmp_color, false, true);

							s_porog = y_b + (height * (1 - static_cast<float>(curr_strob.por) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, tmp_color,(curr_osc_par.curr_strb == ii));
						}
						else
						{
							/*строб АК яркость падает с повышением уровня(самый тусклый extra_por[1])*/
							QColor tmp_color = QColor::fromHsv(hue, 0.4f*strat, 0.5f*(255-value)+value);

							s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.strb_info[ii].extra_por[1]) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, tmp_color, false);

							s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.strb_info[ii].sub_extra_por[1]) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, tmp_color, false, true);


							tmp_color.setHsv(hue, 0.6f*strat, 0.25f*(255-value)+value);

							s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.strb_info[ii].extra_por[0]) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, tmp_color, false);

							s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.strb_info[ii].sub_extra_por[0]) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, tmp_color, false, true);


							s_porog = y_b + (height * (1 - static_cast<float>(curr_strob.por) / MAX_AMPL));
							PlotStrob(painter, koeff, s_begin, s_end, s_porog, OscProp->StrobsColor[ii],(curr_osc_par.curr_strb == ii));
						}
					}
					else
					{
						s_porog = y_b + (height * (1 - static_cast<float>(curr_strob.por) / MAX_AMPL));
						PlotStrob(painter, koeff, s_begin, s_end, s_porog, OscProp->StrobsColor[ii],(curr_osc_par.curr_strb == ii));
					}
				}
			}
		}
		else
		{
			float s_begin= curr_us_par.beg_r/TEN_F - OscBegin;
			float s_end= s_begin + 0.001f * cn_info_par.a_step_count * (curr_us_par.step_r + 1) * COEF_B_SCAN;

			float s_porog = y_b + (height * (1 - static_cast<float>(cn_info_par.a_k_color) / MAX_AMPL));

			PlotStrob(painter, koeff, s_begin, s_end, s_porog, OscProp->StrobsColor[1], true);
		}
	}

	painter.setRenderHints(QPainter::Antialiasing, true);

/*
	if(curr_dop_par.thick.on_thick != 0)		// ???
	{
		float cos_alpha = cos( curr_par_us.alpha*3.141592653f/(180.0f*COEF_ALPHA) );
		PlotThickLine(painter, koeff, cos_alpha, curr_dop_par, curr_par_us);	
	}
*/


	if(curr_osc_par.rej_osc && curr_us_par.vrch.on_vrch)
		PlotVRCh(painter, koeff, curr_osc_par, curr_us_par);




	QPen pen1( OscProp->OscillogramColor );

	pen1.setWidthF(OscProp->OscillogramWidth);
	painter.setPen(pen1);

	float plot_x_step = static_cast<float>(width) / (LEN_OSC - 1);
	float plot_y_step = static_cast<float>(height) / MAX_AMPL;

/*	if(curr_dop_par.rej_osc && *p_plot_ogib)
	{
		 QPoint points_arr[LEN_OSC+2];

		 points_arr[0].setX(x_b);
		 points_arr[0].setY(y_b + height - plot_y_step * MIN_AMPL);


		for(int i = 0; i < LEN_OSC; i++)
		{
			points_arr[i+1].setX(x_b + plot_x_step * i);
			points_arr[i+1].setY(y_b + height - plot_y_step * ogib[i]);
		}

		points_arr[LEN_OSC+1].setX(x_b + plot_x_step * (LEN_OSC - 1));
		points_arr[LEN_OSC+1].setY(y_b + height - plot_y_step * MIN_AMPL);


		painter.setRenderHints(QPainter::Antialiasing, false);

		painter.setPen(Qt::NoPen);

		QColor transOgib(OscProp->OgibColor);
		transOgib.setAlpha(110);
		QBrush ogib_brush(transOgib);
		painter.setBrush(ogib_brush);
		painter.drawPolygon(points_arr, LEN_OSC+2);


		painter.setRenderHints(QPainter::Antialiasing, true);

		painter.setBrush(Qt::NoBrush);
		pen1.setColor( OscProp->OgibColor );
		painter.setPen(pen1);

		for(int i = 1; i < (LEN_OSC+2); i++)
			painter.drawLine(points_arr[i-1], points_arr[i]);

		pen1.setColor( OscProp->OscillogramColor );
		painter.setPen(pen1);
	}
	*/
	
	if(curr_osc_par.rej_osc)
	{
		/*заполняем массив точек из принятой эхограммы и отрисовываем*/
		QPoint points_arr[LEN_OSC+2];

		points_arr[0].setX(x_b);
		points_arr[0].setY(y_b + height - plot_y_step * MIN_AMPL);

		for(int i = 0; i < LEN_OSC; i++)
		{
			points_arr[i+1].setX(x_b + plot_x_step * i);
			points_arr[i+1].setY(y_b + height - plot_y_step * curr_ehogr.osc[i]);
		}

		points_arr[LEN_OSC+1].setX(x_b + plot_x_step * (LEN_OSC - 1));
		points_arr[LEN_OSC+1].setY(y_b + height - plot_y_step * MIN_AMPL);


		for(int i = 1; i < (LEN_OSC+2); i++)
			painter.drawLine(points_arr[i-1], points_arr[i]);

		if(curr_us_par.rej & TD_TOL)
			PlotUsTimes(painter, koeff, OscBegin);
	}
	else
	{
		QPoint points_arr[LEN_OSC];

		for(int i = 0; i < LEN_OSC; i++)
		{
			points_arr[i].setX(x_b + plot_x_step * i);
			points_arr[i].setY(y_b + height - plot_y_step * curr_ehogr.osc[i]);
		}

		for(int i = 1; i < LEN_OSC; i++)
			painter.drawLine(points_arr[i-1], points_arr[i]);
	}

	painter.setRenderHints(QPainter::Antialiasing, false);
}



void OscillogramPlotterSetter::PlotRespond(const osc_struct_t &curr_ehogr, const par_osc_t &curr_osc_par, const par_us_t &curr_us_par, const cn_info_t &cn_info_par, const view_cn_info_t &curr_view_cn_par)
{
	if(pixmap_width != 0 && pixmap_height != 0)
	{
		QPainter painter(pixmap);

		if(!painter.isActive())
			return;


		painter.fillRect(0, 0, pixmap_width, pixmap_height, OscProp->BackgroundColor );

		DrawGrid(painter);//рисует горизонтальные линии

		if(curr_osc_par.rej_osc)
		{
			if(curr_view_cn_par.axis_mode.axis_y_mode)
				PlotLogarithmicVerticalSignature(painter, curr_us_par.strb[curr_osc_par.curr_strb].por );
			else
				PlotVerticalSignature(painter);
		}
		else
			PlotVerticalSignatureRadio(painter);

		PlotHorizontalSignature(painter, curr_osc_par, cn_info_par, curr_view_cn_par);//рисует вертикальные линии и подписывает значения
		
		/*отображает значение толщины в правом верхнем углу, если режим выбранного канала толщинометрия*/
		if(((curr_us_par.rej & TD_TOL) || ((curr_us_par.rej & TD_TOL_LAM) && curr_us_par.strb[2].on_strb)) && (*p_sub_thick >= 0.0f))
		{
			QPen text_pen( OscProp->TextColor );
			painter.setPen(text_pen);

			QFont font = painter.font();
			QFont font1(font);
		
			font1.setPixelSize(2*frame_width);
			painter.setFont(font1);
			QRect rect( x_b + width/3, y_b, 2*width/3, 3*y_b);

			painter.drawText(rect, Qt::AlignRight | Qt::AlignTop, QString::number(*p_sub_thick, 'f', 3) );	

			painter.setFont(font);
		}


		PlotRespond(painter, curr_ehogr, curr_osc_par, curr_us_par, cn_info_par, curr_view_cn_par);//отрисовывает стробы и текущую эхограмму
	}


	if(&curr_ehogr != &Old_ehogr_struct)
	{
		Old_ehogr_struct = curr_ehogr;

		Old_osc_par = curr_osc_par;
		Old_us_par = curr_us_par;
		Old_cn_info_par = cn_info_par;
		Old_view_cn_par = curr_view_cn_par;

		if(!AnyReceived)
			AnyReceived = true;
	}

	if(pixmap_width != 0 && pixmap_height != 0)
		UpdatePlot();
}


void OscillogramPlotterSetter::OutFrameText(QPainter & painter, const QString & string, const int x_rightMid, const int y_rightMid, const int size1, const int legth)
{
	QRect rect( x_rightMid - legth, y_rightMid - size1 , legth, size1);
	painter.drawText(rect, Qt::AlignCenter, string);
}


void OscillogramPlotterSetter::PlotVerticalSignature(QPainter & painter)
{
	int count_y =  y_sign_step / y_step + 1;

	if(count_y == 0)
		count_y = 1;

	int num_count = OscProp->row_number / count_y;
		
	float y_val_step = 255.0f * count_y / OscProp->row_number ;	//100.0f //255.0f
	float y_val = 0.5f;
	float y_pos = y_b + frame_width/2 + height;


	QPen pen1( OscProp->TextColor );
	painter.setPen(pen1);

	QFont front = painter.font();
	front.setPixelSize(font_size);
	painter.setFont(front);

	for(int i = 0; i <= num_count ; i++)
	{
		OutFrameText(painter, QString::number(static_cast<int>(y_val), 10), x_b, y_pos, frame_width, frame_width);

		y_val += y_val_step;
		y_pos -= count_y * y_step;
	}

//	OutFrameText(painter, "%", x_b + frame_width/2, y_b, frame_width, frame_width);
}


void OscillogramPlotterSetter::PlotVerticalSignatureRadio(QPainter & painter)
{
	int count_y =  y_sign_step / y_step + 1;

	if(count_y == 0)
		count_y = 1;

	int num_count = OscProp->row_number / count_y;
		
	float y_val_step = 256.0f * count_y / OscProp->row_number ;
	float y_val = -128.5f;
	float y_pos = y_b + frame_width/2 + height;


	QPen pen1( OscProp->TextColor );
	painter.setPen(pen1);

	QFont front = painter.font();
	front.setPixelSize(font_size);
	painter.setFont(front);

	for(int i = 0; i <= num_count ; i++)
	{
		OutFrameText(painter, QString::number(static_cast<int>(y_val), 10), x_b, y_pos, frame_width, frame_width);

		y_val += y_val_step;
		y_pos -= count_y * y_step;
	}
}

void OscillogramPlotterSetter::PlotLogarithmicVerticalSignature(QPainter & painter, const quint8 curr_porog)
{
	if(curr_porog == 0)
		return;

	int count_y =  y_sign_step / y_step + 1;

	if(count_y == 0)
		count_y = 1;

	int num_count = OscProp->row_number / count_y;
	
	float y_val_step = 255.0f * count_y / OscProp->row_number ;

	float y_val = 0;
	float y_pos = y_b + frame_width/2 + height;


	QPen pen1( OscProp->TextColor );
	painter.setPen(pen1);

	QFont front = painter.font();
	front.setPixelSize(font_size);
	painter.setFont(front);

	OutFrameText(painter, QString::number( 20*log10(1.0f/curr_porog), 'f', 1), x_b, y_pos, frame_width, frame_width);

	for(int i = 1; i <= num_count ; i++)
	{
		y_val += y_val_step;
		y_pos -= count_y * y_step;

		OutFrameText(painter, QString::number( 20*log10(y_val/curr_porog), 'f', 1), x_b, y_pos, frame_width, frame_width);
	}

	OutFrameText(painter, tr("\320\264\320\221"), x_b + frame_width/2, y_b, frame_width, frame_width);
}




void OscillogramPlotterSetter::PlotHorizontalSignature(QPainter & painter, const par_osc_t &curr_osc_par, const cn_info_t &cn_info_par, const view_cn_info_t &curr_view_cn_par)
{
	float FullOscLen=(curr_osc_par.curr_stp_r + 1) * LEN_OSC * STEP_KOEF;
	float x_val = curr_osc_par.curr_beg_r/TEN_F; 

	QPen pen1(OscProp->GridColor);
	pen1.setWidth(1);
	painter.setPen(pen1);

	QPen pen2( OscProp->TextColor );

	QFont front = painter.font();
	front.setPixelSize(font_size);
	painter.setFont(front);

	float x_val_per_pix = FullOscLen / width ;			// приращение, приходящееся на 1 пиксель

	if(!curr_osc_par.rej_osc)
		x_val_per_pix = 0.025f  * LEN_OSC / width ;

	float alpha = cn_info_par.probe_par.alpha*3.141592653f/(180.0f*COEF_ALPHA);


//	bool is_thick_measure = false;		// работает только в случае (curr_par.par_dop.axis_x_mode == 1) и (curr_par.par_dop.thick.on_thick)


		
	switch(curr_view_cn_par.axis_mode.axis_x_mode)
	{
	case 0:
		if((cn_info_par.rej != TD_TOL) && (cn_info_par.rej != TD_TOL_REZ))
			x_val = x_val - 0.002f * cn_info_par.probe_par.t_pr;
		break;
				
	case 1:
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
				
	case 2:
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
	double grid_elem_pow = log10(grid_elem_count);
		
		
	QLine line;
		
	if(grid_elem_pow > 0)	// т.е. более 1 элемента на клетку
	{
		int dec_elem_pow = (int)grid_elem_pow;
		int value_incrim = 1;
			
		if( (grid_elem_pow - dec_elem_pow) > 0.699 )	// > (log10(5)) т.е. умножаем ещё на 5
			value_incrim *= 5;
		else if( (grid_elem_pow - dec_elem_pow) > 0.301 )	// т.е. умножаем ещё на 2
			value_incrim *= 2;
			
		for(int i = 0; i < dec_elem_pow; i++)
			value_incrim *= 10;					// итого получаем, на сколько смещаемся в элементах
			
			
		float x_val_step = value_incrim / x_val_per_pix;		// пикселей в приращении 
			


		{
			
			int x_curr_val;
			
			if(x_val > 0)
				x_curr_val = (int)(x_val / value_incrim) + 1;
			else
				x_curr_val = (int)(x_val / value_incrim);
			
			x_curr_val *= value_incrim;
			

			float x_curr_pos = x_curr_val - x_val;		// от начала до первого значения в единицах 
			x_curr_pos /= x_val_per_pix;				// в пикселях
			
			x_curr_pos += x_b;

			float temp_x_pos = x_sign_step;
			
			while(x_curr_pos < (x_b + width))
			{
				if(x_curr_val >= 0)
				{
					if(temp_x_pos >= x_sign_step)
					{
						painter.setPen(pen2);
						OutFrameText(painter, QString::number(x_curr_val, 10), frame_width/2 + (int)x_curr_pos,  pixmap_height, frame_width, frame_width);		
						painter.setPen(pen1);

						line.setLine( x_curr_pos, y_b, x_curr_pos, y_b + height + 5);
						painter.drawLine(line);

						temp_x_pos = 0;
					}
					else
					{
						line.setLine( x_curr_pos, y_b, x_curr_pos, y_b + height);
						painter.drawLine(line);
					}
					
					temp_x_pos += x_val_step;
				}
				else
				{
						line.setLine( x_curr_pos, y_b, x_curr_pos, y_b + height);
						painter.drawLine(line);
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
			x_curr_pos += x_b;	
			
			float temp_x_pos = x_sign_step;	
				
			while(x_curr_pos < (x_b + width))
			{
				if(x_curr_val >= 0)
				{
					if(temp_x_pos >= x_sign_step)
					{
						painter.setPen(pen2);
						OutFrameText(painter, QString::number(x_curr_val, 'f', 1), frame_width/2 + (int)x_curr_pos,  pixmap_height, frame_width, frame_width);
						painter.setPen(pen1);

						line.setLine( x_curr_pos, y_b, x_curr_pos, y_b + height + 5);
						painter.drawLine(line);

						temp_x_pos = 0;
					}
					else
					{
						line.setLine( x_curr_pos, y_b, x_curr_pos, y_b + height);
						painter.drawLine(line);
					}
					temp_x_pos += x_val_step;
				}
				else
				{
					line.setLine( x_curr_pos, y_b, x_curr_pos, y_b + height);
					painter.drawLine(line);
				}
				
				x_curr_val += value_incrim;
				x_curr_pos += x_val_step;	
			}

		}

	}
		
	painter.setPen(pen2);
		
		
	switch(curr_view_cn_par.axis_mode.axis_x_mode)
	{
	case 0:
		OutFrameText(painter, tr("mcs"), pixmap_width, pixmap_height - frame_width/2, frame_width, frame_width);
		break;
	case 1:
		OutFrameText(painter, tr("\320\274\320\274"), pixmap_width, pixmap_height - frame_width/2, frame_width, frame_width);
		OutFrameText(painter, tr("Y"), pixmap_width, pixmap_height - frame_width, frame_width, frame_width);
		break;
	case 2:
		OutFrameText(painter, tr("\320\274\320\274"), pixmap_width, pixmap_height - frame_width/2, frame_width, frame_width);
		OutFrameText(painter, tr("X"), pixmap_width, pixmap_height - frame_width, frame_width, frame_width);
		break;
	}
}


void OscillogramPlotterSetter::PlotStrob(	QPainter & painter, 
											const float koeff, 
											float s_begin, 
											float s_end, 
											const float porog1, 
											QColor color, 
											const bool selected,
											const bool stipple)
{
	bool s_to_plot = true;
	QPen pen1( color );

	pen1.setWidthF(2);
	pen1.setCapStyle(Qt::FlatCap);
	painter.setPen(pen1);

	float half_strob_width=OscProp->StrobWidth/2.0;
	if((s_begin >= 0) && (s_end * koeff <= width))
	{
		if(selected)
		{
			PlotStrobSetEnd(painter, x_b + koeff * s_end, porog1 + OscProp->StrobWidth/2);
			PlotStrobSetEnd(painter, x_b + koeff * s_begin + 1, porog1 + OscProp->StrobWidth/2);
		}
	}

	if(s_begin < 0)
	{
		if(s_end * koeff > ArrowIndent)
		{
			s_begin = ArrowIndent / koeff;
			PlotStrobArrow(painter, x_b,  porog1 + half_strob_width, true);

			if(selected)
				PlotStrobSetEnd(painter, x_b + koeff * s_end, porog1 + OscProp->StrobWidth/2);
		}
		else
		{
			s_to_plot = false;

			PlotStrobArrow(painter, x_b, porog1 + half_strob_width, true);
			PlotStrobArrow(painter, x_b + ArrowInterval, porog1 + half_strob_width, true);
		}
	}

	if(s_end * koeff > width)
	{
		if(s_begin * koeff< (width - ArrowIndent))
		{
			s_end = (width - ArrowIndent) / koeff;
			PlotStrobArrow(painter, x_b + width, porog1 + half_strob_width, false);

			if(selected)
				PlotStrobSetEnd(painter, x_b + koeff * s_begin + 1, porog1 + OscProp->StrobWidth/2);
		}
		else
		{
			s_to_plot = false;

			PlotStrobArrow(painter, x_b + width, porog1 + half_strob_width, false);
			PlotStrobArrow(painter, x_b + width - ArrowInterval, porog1 + half_strob_width, false);
		}
	}

	if(s_to_plot)
	{
		pen1.setWidthF(OscProp->StrobWidth);
		if(stipple)
			pen1.setStyle(Qt::DashLine);

		painter.setPen(pen1);
		QLine line( x_b + koeff * s_begin, porog1 + OscProp->StrobWidth/2 , x_b + koeff * s_end, porog1 + OscProp->StrobWidth/2 );
		painter.drawLine(line);
	}
}


void OscillogramPlotterSetter::PlotStrobArrow(QPainter & painter, const float x0, const float y0, const bool left)
{
	painter.save();
	QPen curr_pen=painter.pen();
	curr_pen.setJoinStyle(Qt::MiterJoin);
	painter.setPen(curr_pen);
	if(left)
	{
		QLine line( x0, y0 , x0 + ArrowDim, y0 - ArrowDim );
		painter.drawLine(line);

		line.setLine( x0, y0 , x0 + ArrowDim, y0 + ArrowDim );
		painter.drawLine(line);
	}
	else
	{
		QLine line( x0, y0 , x0 - ArrowDim, y0 - ArrowDim );
		painter.drawLine(line);

		line.setLine( x0, y0 , x0 - ArrowDim, y0 + ArrowDim );
		painter.drawLine(line);
	}
	painter.restore();
}

void OscillogramPlotterSetter::PlotStrobSetEnd(QPainter & painter, const float x0, const float y0)
{
	QLine line( x0, y0 - StrobSetHeight , x0, y0 + StrobSetHeight);
	painter.drawLine(line);
}



float OscillogramPlotterSetter::GetVRChPorog(const par_vrch_t &vrch_pars, const quint8 i, const quint8 tact_kUs) const
{
	if(vrch_relative_mode)
	{
		if(tact_kUs == MAX_KUS)
			return y_b;
		return y_b + height *(0.5f - vrch_pars.kus[i]/(2.0f*(MAX_KUS-tact_kUs))) ;
	}

	return y_b + height *(1.0f - static_cast<float>(tact_kUs + vrch_pars.kus[i] )/MAX_KUS ) ;
}

void OscillogramPlotterSetter::PlotVRChPoint(QPainter & painter, const QPen &base_pen, const QPen &point_pen, const QBrush &pointBrush, const QPoint &point)
{
	painter.setPen(point_pen);
	painter.setBrush(pointBrush);
	painter.drawEllipse(point, VRChPtRadius, VRChPtRadius);
	painter.setBrush(Qt::NoBrush);
	painter.setPen(base_pen);
}

void OscillogramPlotterSetter::PlotVRChSelectedPoint(QPainter & painter, const QPen &base_pen,const QPoint &point)
{
	QPen vrch_selPen(OscProp->StrobsColor[1]);
	vrch_selPen.setWidth(OscProp->OscillogramWidth);

	painter.setPen(vrch_selPen);
	painter.setBrush(QBrush(OscProp->MarkerColor, Qt::SolidPattern));
	painter.drawEllipse(point, VRChPtRadius, VRChPtRadius);

	QLine cross_line(point.x() - VRChPtIndent, point.y(), point.x() - VRChPtCrossDim/2, point.y());
	painter.drawLine(cross_line);

	cross_line.setLine(point.x(), point.y() - VRChPtIndent, point.x(), point.y() - VRChPtCrossDim/2);
	painter.drawLine(cross_line);


	cross_line.setLine(point.x() + VRChPtIndent, point.y(), point.x() + VRChPtCrossDim/2, point.y());
	painter.drawLine(cross_line);

	cross_line.setLine(point.x(), point.y() + VRChPtIndent, point.x(), point.y() + VRChPtCrossDim/2);
	painter.drawLine(cross_line);

	painter.setBrush(Qt::NoBrush);
	painter.setPen(base_pen);
}

void OscillogramPlotterSetter::PlotVRChLine(QPainter & painter, 
											const QPen &base_pen, 
											const QPen &point_pen, 
											const QBrush &pointBrush, 
											const float x1, 
											const float y1, 
											const float x2, 
											const float y2, 
											const bool plot_point,
											const bool selected_point)
{

	if(y1 < y_b + 1)
	{
		if(y2 < y_b + 1)
		{
			QLine line( x1, y_b + 1, x2, y_b + 1 );
			painter.drawLine(line);
		}
		else
		{
			float tang = (y2 - y1) / (x2 - x1);
			float x_mid = x1 + (y_b + 1 - y1)/tang;

			QLine line( x1, y_b + 1, x_mid, y_b + 1 );
			painter.drawLine(line);
			line.setLine( x_mid, y_b + 1, x2, y2 );
			painter.drawLine(line);
		}
		if(plot_point)
		{
			if(selected_point)
				PlotVRChSelectedPoint(painter, base_pen, QPoint(x1, y_b + 1));
			else
				PlotVRChPoint(painter, base_pen, point_pen, pointBrush, QPoint(x1, y_b + 1));
		}
	}
	else
	{
		if(y2 < y_b + 1)
		{
			float tang = (y2 - y1) / (x2 - x1);
			float x_mid = x1 + (y_b + 1 - y1)/tang;

			QLine line( x1, y1, x_mid, y_b + 1 );
			painter.drawLine(line);
			line.setLine( x_mid, y_b + 1, x2, y_b + 1 );
			painter.drawLine(line);
		}
		else
		{
			QLine line( x1, y1, x2, y2 );
			painter.drawLine(line);
		}
		if(plot_point)
		{
			if(selected_point)
				PlotVRChSelectedPoint(painter, base_pen, QPoint(x1, y1));
			else
				PlotVRChPoint(painter, base_pen, point_pen, pointBrush, QPoint(x1, y1));
		}
	}
}

void OscillogramPlotterSetter::PlotVRCh(QPainter & painter, 
										const float koeff, 
										const par_osc_t &osc_par, 
										const par_us_t &us_par)
{
	QPen vrchPen( OscProp->VRChColor );
	QPen pointPen( OscProp->StrobsColor[NUM_STRBS-1] );
	QBrush pointBrush(OscProp->VRChColor, Qt::SolidPattern);


	vrchPen.setWidthF(OscProp->OscillogramWidth);
	painter.setPen(vrchPen);

	int i = 0;

	float s_coord = (us_par.vrch.time[0] + 3) - osc_par.curr_beg_r/TEN_F;
	float s_coord_l = s_coord;


	if(s_coord > 0)
	{
		if(s_coord * koeff > width)
			s_coord = width / koeff;

		float OldPor = GetVRChPorog(us_par.vrch, i, us_par.kus);
		PlotVRChLine(painter, vrchPen, pointPen, pointBrush, x_b, OldPor, x_b + koeff * s_coord, OldPor, false, false);
	}

	i++;

	while((i < us_par.vrch.num_p) && (s_coord * koeff < width))
	{
		s_coord_l = s_coord;
		s_coord = (us_par.vrch.time[i] + 3) - osc_par.curr_beg_r/TEN_F;

		if(s_coord > 0)
		{
			if(s_coord_l < 0)
			{
				float coord_y1 = GetVRChPorog(us_par.vrch, i - 1, us_par.kus);
				float coord_y2 = GetVRChPorog(us_par.vrch, i, us_par.kus);
				float tang = (coord_y2 - coord_y1) / (s_coord - s_coord_l);

				if(s_coord * koeff >= width)
				{
					float b = coord_y1 - s_coord_l*tang;
					PlotVRChLine(painter, vrchPen, pointPen, pointBrush, x_b, b, x_b + width, tang * width / koeff + b, false, false);
				}
				else
				{
					PlotVRChLine(painter, vrchPen, pointPen, pointBrush, x_b, coord_y1 - tang * s_coord_l, x_b + koeff * s_coord, coord_y2, false, false);
				}
			}
			else if(s_coord * koeff >= width)
			{
				float coord_y1 = GetVRChPorog(us_par.vrch, i - 1, us_par.kus);
				float coord_y2 = GetVRChPorog(us_par.vrch, i, us_par.kus);
				float tang = (coord_y2 - coord_y1) / (s_coord - s_coord_l) ;

				PlotVRChLine(painter, vrchPen, pointPen, pointBrush,
									x_b + koeff * s_coord_l, coord_y1, x_b + width, 
									coord_y2 - (s_coord - width / koeff) * tang, 
									true,
									osc_par.curr_pvrch == (i-1));
			}
			else
				PlotVRChLine(painter, vrchPen, pointPen, pointBrush,
											x_b + koeff * s_coord_l, GetVRChPorog( us_par.vrch, i - 1, us_par.kus), 
											x_b + koeff * s_coord, GetVRChPorog( us_par.vrch, i, us_par.kus), 
											true,
											osc_par.curr_pvrch == (i-1));
		}
		i++;
	}

	i--;

	if(s_coord * koeff < width)
	{
		if(s_coord < 0)
			s_coord = 0;

		float OldPor = GetVRChPorog(us_par.vrch, i, us_par.kus);

		if(OldPor < y_b)
			OldPor = y_b;

		PlotVRChLine(painter, vrchPen, pointPen, pointBrush, x_b + koeff * s_coord, OldPor, x_b + width, OldPor, true, osc_par.curr_pvrch == i);
	}

	PlotVRChVerticalSignature(painter, us_par.kus);
}


void OscillogramPlotterSetter::PlotVRChVerticalSignature(QPainter & painter, const quint8 tact_kUs)
{
	QPen pen1( OscProp->TextColor );
	painter.setPen(pen1);

	QFont front = painter.font();
	front.setPixelSize(font_size);
	painter.setFont(front);

	int count_y =  y_sign_step / y_step + 1;

	if(count_y == 0)
		count_y = 1;

	int num_count = OscProp->row_number / count_y;
	

	float x_pos = x_b + width + frame_width;
	float y_val_step = MAX_KUS * static_cast<float>(count_y) / OscProp->row_number;
	float y_val = 0.5f;
	float y_pos = y_b + frame_width/2 + height;


	if(vrch_relative_mode)
	{
		if(MAX_KUS == tact_kUs)
			return;

		y_val_step = (MAX_KUS - tact_kUs) * 2 * static_cast<float>(count_y) / OscProp->row_number;
		y_val = tact_kUs - 0.5*num_count*y_val_step;
		y_pos = y_b + frame_width/2 + height;
	}



	y_val += y_val_step;
	y_pos -= count_y * y_step;


	for(int i = 1; i <= num_count ; i++)
	{
		if(vrch_relative_mode)
		{
			if( (i >= num_count/2) && (y_val > 0))
				OutFrameText(painter, QString::number(static_cast<int>(y_val), 10), x_pos, y_pos, frame_width, frame_width);
		}
		else
		{
			if(y_val >= tact_kUs)	//(y_val+y_val_step) >= tact_kUs
				OutFrameText(painter, QString::number(static_cast<int>(y_val) - tact_kUs, 10), x_pos, y_pos, frame_width, frame_width);
		}

			
		y_val += y_val_step;
		y_pos -= count_y * y_step;
	}


//	painter.fillRect( QRect(x_b + width - frame_width/2, 0, frame_width, frame_width), OscProp->BackgroundColor );

	OutFrameText(painter, tr("dB"), x_b + width + frame_width/2, y_b, frame_width, frame_width);
}


void OscillogramPlotterSetter::PlotUsTimes(QPainter & painter, const float koeff, const float OscBegin)
{
	QPen us_line_pen( OscProp->MarkerColor );
	us_line_pen.setWidthF(0.8f);
	us_line_pen.setStyle(Qt::DashLine);

	painter.setPen(us_line_pen);


	for(quint8 i = 0; i < NUM_RESULT_STRBS; i++)
	{
		if(p_us_times->ampl[i].time > 0)
		{
			float cross_pos =  (p_us_times->ampl[i].time * TIME_UNIT * 0.5f - OscBegin)*koeff;
			if(cross_pos > 0 && (cross_pos < width))
				painter.drawLine(x_b + cross_pos, y_b, x_b + cross_pos, y_b + height);
		}
	}
}




/*
void OscillogramPlotterSetter::PlotThickLine(	QPainter & painter, 
												float koeff,
												const float cos_alpha,
												const par_dop_t &par_dop, 
												const par_us_t &uss)
{

	float thick_val = par_dop.thick.thick_val * 0.1f;	// в мм
		
	if(thick_val == 0.0f || (cos_alpha == 0.0f))
		return;


		
	painter.save();	
	// ограничение области прорисовки 

	painter.setClipRect(x_b, y_b - OscProp->OscillogramWidth, width, height + OscProp->OscillogramWidth);	
	


	QPen thick_Pen(OscProp->TextColor);
	thick_Pen.setWidth(OscProp->OscillogramWidth);
	thick_Pen.setStyle(Qt::DashLine);
	painter.setPen(thick_Pen);


	// определение точки начала отсчёта
		 
		 
	float x_val = par_dop.curr_begr * 0.1f;	// начальное значение осциллограммы
	 
		
	//koeff  = width / FullOscLen;
		
		
	if(par_dop.rej_osc == 0)
		koeff  *=  40.0f ;
		
	
		
	float mks_thick = thick_val * 2000.0f / (uss.cc * cos_alpha) ;	// в мкс ??
		
	
	// точка начала линии ???	
		
	float mks_thick_displ = 0.002f *uss.t_pr - x_val;
		
		
	// koeff - пикс / мкс
		
	mks_thick_displ *= koeff;		// переходим от мкс к пикселям
	mks_thick *= koeff;
	

		
	if(mks_thick_displ > 0.0f)
	{
			
		if(mks_thick_displ >= width)	// линию не видно совсем...
			return;
		

		// рисуем линии с самого начала

		beam_line.resize(0);
		beam_line.push_back(QPoint(x_b + mks_thick_displ, y_b));
					
		bool up = true;	
		while(mks_thick_displ < width)
		{
			mks_thick_displ += mks_thick;
			beam_line.push_back( QPoint(x_b + mks_thick_displ, y_b + (up ? height/3 : 0)) );
			up = !up;
		}

		for(int i = 1; i < beam_line.size(); i++)
			painter.drawLine(beam_line[i-1], beam_line[i]);

	}
	else	// начала не видно
	{		// от лишней линии ничего не будет
			
		int num_full_periods = (int) ((-mks_thick_displ)/(2*mks_thick));
			
		mks_thick_displ += num_full_periods * 2 * mks_thick;			// ???
		

		beam_line.resize(0);
		beam_line.push_back(QPoint(x_b + mks_thick_displ, y_b));			
		
		bool up = true;	
		while(mks_thick_displ < width)
		{
			mks_thick_displ += mks_thick;
			beam_line.push_back( QPoint(x_b + mks_thick_displ, y_b + (up ? height/3 : 0)) );
			up = !up;
		}
			
		for(int i = 1; i < beam_line.size(); i++)
			painter.drawLine(beam_line[i-1], beam_line[i]);
			
	}
		 
	painter.restore();
}
*/


bool OscillogramPlotterSetter::IsInsidePlot(const float x, const float y) const
{
	return (x >= x_b) && (x <= x_b + width) && (y >= y_b) && (y <= y_b + height);
}

bool OscillogramPlotterSetter::IsInsideBeginOsc(const float x, const float y) const
{
	return (y > y_b + height + StrobSetHeight/2 + 2) && (x < (width + 2*left)/4 );
}

bool OscillogramPlotterSetter::IsInsideEndOsc(const float x, const float y) const
{
	return (y > y_b + height + StrobSetHeight/2 + 2) && (x > 3*(width + 2*left)/4 );
}


bool OscillogramPlotterSetter::IsInsideAxisX(const float x, const float y) const
{
	return (y > y_b + height + StrobSetHeight/2 + 2) && (x > (width + 2*left)/4 ) && (x < 3*(width + 2*left)/4 );
}

bool OscillogramPlotterSetter::IsInsideAxisY(const float x, const float y) const
{
	return (x <= x_b - 6) && (y >= y_b) && (y <= y_b + height);
}




bool OscillogramPlotterSetter::IsInsideStrobVisible(const float koeff, const float s_begin, const float s_end) const
{
	return (s_begin < width) && ((s_end * koeff) >= 0);	//	return (s_begin*koeff < width) && ((s_end * koeff) >= 0);	//(s_begin >= 0 && ((s_end * koeff) <= width));
}

bool OscillogramPlotterSetter::IsInsideStrobLeft(const float koeff, const float s_begin, const float s_end, const float s_porog, const float x, const float y) const
{
	float x_min = x_b + koeff * s_begin - 24;
	float x_max = x_b + koeff * s_begin + 6;

	float y_min = s_porog - StrobSetHeight;
	float y_max = s_porog + StrobSetHeight;

	return (x >= x_min) && (x < x_max) && (y >= y_min) && (y <= y_max);
}

bool OscillogramPlotterSetter::IsInsideStrobMiddle(const float koeff, const float s_begin, const float s_end, const float s_porog, const float x, const float y) const
{
	float x_min = x_b + koeff * s_begin + 6;
	float x_max = x_b + koeff * s_end - 6;

	float y_min = s_porog - StrobSetHeight;
	float y_max = s_porog + StrobSetHeight;

	return (x >= x_min) && (x <= x_max) && (y >= y_min) && (y <= y_max);
}

bool OscillogramPlotterSetter::IsInsideStrobRight(const float koeff, const float s_begin, const float s_end, const float s_porog, const float x, const float y) const
{
	float x_min = x_b + koeff * s_end - 6;
	float x_max = x_b + koeff * s_end + 24;

	float y_min = s_porog - StrobSetHeight;
	float y_max = s_porog + StrobSetHeight;

	return (x > x_min) && (x <= x_max) && (y >= y_min) && (y <= y_max);
}


bool OscillogramPlotterSetter::IsInsideVRChPoint(const int i, const float koeff, const float x, const float y) const
{
	float x_coord = x_b + koeff * ((Old_us_par.vrch.time[i] + 3) - Old_osc_par.curr_beg_r/TEN_F);
	float y_coord = 0;

	if(vrch_relative_mode)
	{
		if(Old_us_par.kus == MAX_KUS)
			y_coord = y_b;

		y_coord = y_b + height *(0.5f - static_cast<float>(Old_us_par.vrch.kus[i])/(MAX_KUS-Old_us_par.kus)) ;
	}
	else
		y_coord = y_b + height *(1.0f - static_cast<float>(Old_us_par.kus + Old_us_par.vrch.kus[i] )/MAX_KUS ) ;


	if(y_coord < y_b)
		return (x > (x_coord - VRChPtCrossDim)) && (x <= (x_coord + VRChPtCrossDim)) && (y >= (y_b - VRChPtCrossDim)) && (y <= (y_b + VRChPtCrossDim));

	return (x > (x_coord - VRChPtCrossDim)) && (x <= (x_coord + VRChPtCrossDim)) && (y >= (y_coord - VRChPtCrossDim)) && (y <= (y_coord + VRChPtCrossDim));
}




void OscillogramPlotterSetter::TestNewPosition(const QPointF &rel_pos)
{
	PositionTesterPlotter::TestNewPosition(rel_pos);
/*	if(is_dragging)*/
#if 1
	if(is_dragging)
	{
		switch(curr_area)
		{
		case InBeginOsc:
			emit BegOscIntermedChange(CalculateCurrOscBeg());
			break;
		case InEndOsc:
			emit EndOscIntermedChange(CalculateCurrOscEnd());
			break;

		case InStrobLeft:
			if(Old_us_par.rej != TD_B_SCAN)
			{
				float koeff  = ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F) / width;

				int new_beg;
				int new_len;

				int length_displ = koeff * (curr_x - drag_start_x);


				if(-length_displ > Refference_us_par.strb[_curr_strob].beg)
					length_displ = - Refference_us_par.strb[_curr_strob].beg;

				new_len = Refference_us_par.strb[_curr_strob].len;
				if(length_displ > new_len)
				{
					length_displ = new_len;
					new_len = 0;
				}
				else
					new_len = new_len - length_displ;

				new_beg = Refference_us_par.strb[_curr_strob].beg + length_displ;


 				emit SetStrobIntermedLeft(_curr_strob,  new_beg, new_len);
			}
			else
			{
				float koeff  = ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F) / width;

				int length_displ = koeff * (curr_x - drag_start_x);


				if(-length_displ > Refference_us_par.beg_r)
					length_displ = - Refference_us_par.beg_r;

				int new_len = 0.01f*Refference_cn_info_par.a_step_count * (Refference_us_par.step_r + 1) * COEF_B_SCAN;

				if(length_displ > new_len)
				{
					length_displ = new_len;
					new_len = 0;
				}
				else
					new_len = new_len - length_displ;


				qint16 step_count = 100.0f*new_len/( (Refference_us_par.step_r + 1) * COEF_B_SCAN);

				if(step_count < MIN_B_SCAN_LEN)
					step_count = MIN_B_SCAN_LEN;
				else if(step_count > MAX_B_SCAN_LEN)
					step_count = MAX_B_SCAN_LEN;



				int new_beg = Refference_us_par.beg_r + length_displ;

				emit SetBScanIntermedLeft(new_beg, step_count);
			}
			break;

		case InStrobMiddle:
			if(Old_us_par.rej != TD_B_SCAN)
			{
				float koeff  = ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F) / width;

				int new_beg = Refference_us_par.strb[_curr_strob].beg + koeff * (curr_x - drag_start_x);
				if(new_beg < 0)
					new_beg = 0;

				int new_porog = Refference_us_par.strb[_curr_strob].por - (curr_y - drag_start_y) / height * MAX_AMPL;
				if(new_porog < MIN_POR)
					new_porog = MIN_POR;
				if(new_porog > MAX_POR)
					new_porog = MAX_POR;

				emit SetStrobIntermedPos(_curr_strob, new_beg, new_porog);
			}
			else
			{
				float koeff  = ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F) / width;


				int new_beg = Refference_us_par.beg_r + koeff * (curr_x - drag_start_x);
				int new_porog = Refference_cn_info_par.a_k_color - (curr_y - drag_start_y) / height * MAX_AMPL;

				if(new_porog < MIN_POR)
					new_porog = MIN_POR;

				if(new_beg < 0)
					new_beg = 0;

				if(new_porog > MAX_POR)
					new_porog = MAX_POR;

				emit SetBScanIntermedPos(new_beg, new_porog);
			}
			break;

		case InStrobRight:
			if(Old_us_par.rej != TD_B_SCAN)
				emit SetStrobIntermedRight(_curr_strob, CalculateCurrStrobLen());
			else
			{
				qint16 step_count = 0.01f*Refference_cn_info_par.a_step_count * (Refference_us_par.step_r + 1) * COEF_B_SCAN + (curr_x - drag_start_x) * (Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F / width;

				if(step_count < MIN_B_SCAN_LEN)
					step_count = MIN_B_SCAN_LEN;
				else if(step_count > MAX_B_SCAN_LEN)
					step_count = MAX_B_SCAN_LEN;

				emit SetBScanIntermedRight(step_count);
			}
			break;


		case InStrobExtraPor2:
			{
				int new_porog = Refference_cn_info_par.strb_info[_curr_strob].extra_por[0] - (curr_y - drag_start_y) / height * MAX_AMPL;
				if(new_porog < MIN_POR)
					new_porog = MIN_POR;
				if(new_porog > MAX_POR)
					new_porog = MAX_POR;

				emit SetStrobIntermedExtraPor2(new_porog);
			}
			break;


		case InStrobExtraPor3:
			{
				int new_porog = Refference_cn_info_par.strb_info[_curr_strob].extra_por[1] - (curr_y - drag_start_y) / height * MAX_AMPL;

				if(new_porog < MIN_POR)
					new_porog = MIN_POR;
				if(new_porog > MAX_POR)
					new_porog = MAX_POR;

				emit SetStrobIntermedExtraPor3(new_porog);
			}
			break;


		case InVRChPoint:
			{
				float koeff  = ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF) / width;

				float new_vchT = Refference_us_par.vrch.time[selected_vrch_point] + koeff * (curr_x - drag_start_x);
				if(new_vchT < 0)
					new_vchT = 0;


				float new_vchKUs = 0;
				quint8 limit_k_us=MAX_KUS-Refference_us_par.kus;
				if(selected_vrch_point != 0)
				{
					if(vrch_relative_mode)
					{
						if(Old_us_par.kus == MAX_KUS)
							new_vchKUs = Refference_us_par.vrch.kus[selected_vrch_point];
						else
							new_vchKUs = Refference_us_par.vrch.kus[selected_vrch_point] - (curr_y - drag_start_y)*2.0f*(MAX_KUS-Refference_us_par.kus)/height ;
					}
					else
						new_vchKUs = Refference_us_par.vrch.kus[selected_vrch_point] - MAX_KUS * static_cast<float>(curr_y - drag_start_y) / height ;

					if(new_vchKUs < 0)
						new_vchKUs = 0;
					else if(new_vchKUs > limit_k_us )
						new_vchKUs = limit_k_us ;
				}

				emit SetVRChPointIntermedChange(selected_vrch_point, new_vchKUs, new_vchT);	
					
			}
			break;

		default: ;
		}

		return;
	}

#endif
#if 1
	if( IsInsideBeginOsc(curr_x, curr_y) )
	{
		curr_area = InBeginOsc;

		if(cursor_curr != Qt::SizeHorCursor)
		{
			cursor_curr = Qt::SizeHorCursor;
			cursor_changed = true;
		}
	}
	else if( IsInsideEndOsc(curr_x, curr_y) )
	{
		curr_area = InEndOsc;

		if(cursor_curr != Qt::SizeHorCursor)
		{
			cursor_curr = Qt::SizeHorCursor;
			cursor_changed = true;
		}
	}
	else
	{
		bool any_strob = false;

		float koeff  = (float)width /((Old_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF);
		float OscBegin = Old_osc_par.curr_beg_r/TEN_F;


		if(Old_osc_par.rej_osc)
		{
			if(Old_us_par.rej != TD_B_SCAN)
			{
				for(int ii=0; ii < NUM_STRBS; ii++)
				{
					bool on_strob = Old_us_par.strb[ii].on_strb && !((Old_us_par.rej == TD_TOL_REZ) && (ii == REZ_NO_STROB));

					if(on_strob)
					{
						float s_begin= Old_us_par.strb[ii].beg/TEN_F - OscBegin;
						float s_end= s_begin+ Old_us_par.strb[ii].len/TEN_F;
						float s_porog = y_b + (height * (1 - Old_us_par.strb[ii].por/MAX_FLOAT_OSC));//y_b+height-Old_us_par.strb[ii].por*(height/MAX_FLOAT_OSC)

						if( IsInsideStrobVisible(koeff, s_begin, s_end) )
						{

							if(!_main_widget->get_ed_enabled())	// IsInsideStrobLeft и IsInsideStrobRight при этом не проверяются
							{
								if( IsInsideStrobMiddle(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
								{
									_curr_strob = ii;
									curr_area = InStrobMiddle;
									any_strob = true;
								}
							}
							else if( IsInsideStrobMiddle(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
							{
								any_strob = true;
								_curr_strob = ii;
								curr_area = InStrobMiddle;

								if(cursor_curr != Qt::SizeAllCursor)
								{
									cursor_curr = Qt::SizeAllCursor;
									cursor_changed = true;
								}
							}
							else if( IsInsideStrobLeft(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
							{
								any_strob = true;
								_curr_strob = ii;
								curr_area = InStrobLeft;

								if(cursor_curr != Qt::SizeHorCursor)
								{
									cursor_curr = Qt::SizeHorCursor;
									cursor_changed = true;
								}
							}
							else if( IsInsideStrobRight(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
							{
								any_strob = true;
								_curr_strob = ii;
								curr_area = InStrobRight;

								if(cursor_curr != Qt::SizeHorCursor)
								{
									cursor_curr = Qt::SizeHorCursor;
									cursor_changed = true;
								}
							}
						}
						/*проверки для многоуровневого строба*/
						if(!any_strob && _main_widget->get_ed_enabled() && (ii == Old_osc_par.curr_strb) && Old_cn_info_par.strb_info[ii].on_extra_por)
						{
							s_porog = y_b + (height * (1 - Old_cn_info_par.strb_info[ii].extra_por[0]/MAX_FLOAT_OSC));

							if( IsInsideStrobMiddle(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
							{
								any_strob = true;
								_curr_strob = ii;
								curr_area = InStrobExtraPor2;

								if(cursor_curr != Qt::SizeVerCursor)
								{
									cursor_curr = Qt::SizeVerCursor;
									cursor_changed = true;
								}
							}
							else
							{
								s_porog = y_b + (height * (1 - Old_cn_info_par.strb_info[ii].extra_por[1]/MAX_FLOAT_OSC));

								if( IsInsideStrobMiddle(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
								{
									any_strob = true;
									_curr_strob = ii;
									curr_area = InStrobExtraPor3;

									if(cursor_curr != Qt::SizeVerCursor)
									{
										cursor_curr = Qt::SizeVerCursor;
										cursor_changed = true;
									}
								}
							}
						}


						if(!any_strob && (ii != Old_osc_par.curr_strb) && Old_cn_info_par.strb_info[ii].on_extra_por)	// выбор иного строба
						{

							s_porog = y_b + (height * (1 - Old_cn_info_par.strb_info[ii].extra_por[0]/MAX_FLOAT_OSC));

							if( IsInsideStrobMiddle(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
							{
								any_strob = true;
								_curr_strob = ii;
								curr_area = InStrobExtraPor2;
							}
							else
							{
								s_porog = y_b + (height * (1 - Old_cn_info_par.strb_info[ii].extra_por[1]/MAX_FLOAT_OSC));

								if( IsInsideStrobMiddle(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
								{
									any_strob = true;
									_curr_strob = ii;
									curr_area = InStrobExtraPor3;
								}
							}
						}


					}
				}
			}
			else if(_main_widget->get_ed_enabled())		// для Б-скана стробы не выбираются
			{
				float s_begin= Old_us_par.beg_r/TEN_F - OscBegin;
				float s_end= s_begin + 0.001f * Old_cn_info_par.a_step_count * (Old_us_par.step_r + 1)*COEF_B_SCAN;
				float s_porog = y_b + (height * (1 - Old_cn_info_par.a_k_color/MAX_FLOAT_OSC));


				if( IsInsideStrobMiddle(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
				{
					any_strob = true;
					curr_area = InStrobMiddle;

					if(cursor_curr != Qt::SizeAllCursor)
					{
						cursor_curr = Qt::SizeAllCursor;
						cursor_changed = true;
					}
				}
				else if( IsInsideStrobLeft(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
				{
					any_strob = true;
					curr_area = InStrobLeft;

					if(cursor_curr != Qt::SizeHorCursor)
					{
						cursor_curr = Qt::SizeHorCursor;
						cursor_changed = true;
					}
				}
				else if( IsInsideStrobRight(koeff, s_begin, s_end, s_porog, curr_x, curr_y) )
				{
					any_strob = true;
					curr_area = InStrobRight;

					if(cursor_curr != Qt::SizeHorCursor)
					{
						cursor_curr = Qt::SizeHorCursor;
						cursor_changed = true;
					}
				}
			}


			if(!any_strob)
			{
				if(Old_us_par.vrch.on_vrch)
				{
					int i = Old_us_par.vrch.num_p - 1;

					while((i >=0) && !any_strob)
					{
						if( IsInsideVRChPoint(i, koeff, curr_x, curr_y) )
						{
							any_strob = true;

							selected_vrch_point = i;
							curr_area = InVRChPoint;

							if(_main_widget->get_ed_enabled() && (cursor_curr != Qt::SizeAllCursor))
							{
								cursor_curr = Qt::SizeAllCursor;
								cursor_changed = true;
							}
						}
						i--;
					}
				}
			}
		}


		if(!any_strob)
		{
			if(cursor_curr != Qt::ArrowCursor)
			{
				cursor_curr = Qt::ArrowCursor;
				cursor_changed = true;
			}

			if(IsInsideAxisX(curr_x, curr_y))
				curr_area = InAxisX;
			else if(IsInsideAxisY(curr_x, curr_y))
				curr_area = InAxisY;
			else
				curr_area = Outside;
		}
	}
#endif
}

void OscillogramPlotterSetter::DragStarted()
{
#if 1
	Refference_osc_par = Old_osc_par;
	Refference_us_par = Old_us_par;
	Refference_cn_info_par = Old_cn_info_par;


	switch(curr_area)
	{
	case InStrobMiddle:
		if(Old_us_par.rej != TD_B_SCAN)
			emit SetStrobSelected(_curr_strob);
		if(!_main_widget->get_ed_enabled())
			is_dragging = false;
		break;


	case InStrobExtraPor2:
	case InStrobExtraPor3:
		if(_curr_strob != Old_osc_par.curr_strb)
		{
			emit SetStrobSelected(_curr_strob);
			is_dragging = false;
		}
		if(!_main_widget->get_ed_enabled())
			is_dragging = false;
		break;


	case InVRChPoint:
		emit SetVRChPointSelected(selected_vrch_point);
		if(!_main_widget->get_ed_enabled() )
			is_dragging = false;
		break;

	case InAxisX:
		emit OscAxisXChange();
		is_dragging = false;
		curr_area = Outside;
		break;

	case InAxisY:
		emit OscAxisYChange();
		is_dragging = false;
		curr_area = Outside;
		break;

	case InBeginOsc:
	case InEndOsc:
		break;

	default:
		if(!_main_widget->get_ed_enabled() )
			is_dragging = false;
	}
#endif
}

void OscillogramPlotterSetter::DragEnded()
{
	if(!_main_widget->get_ed_enabled() )
	{
		switch(curr_area)
		{
		case InBeginOsc:
			emit BegOscFinalChange();
			break;
		case InEndOsc:
			emit EndOscFinalChange();
			break;

		default: ;
		}
		return;
	}

	switch(curr_area)
	{
	case InBeginOsc:
		emit BegOscFinalChange();
		break;
	case InEndOsc:
		emit EndOscFinalChange();
		break;

	case InStrobLeft:
		if(Old_us_par.rej != TD_B_SCAN)
			emit SetStrobFinalLeft();
		else
			emit SetBScanFinalLeft();
		break;

	case InStrobMiddle:
		if(Old_us_par.rej != TD_B_SCAN)
			emit SetStrobFinalPos();
		else
			emit SetBScanFinalPos();
		break;

	case InStrobRight:
		if(Old_us_par.rej != TD_B_SCAN)
			emit SetStrobFinalRight();
		else
			emit SetBScanFinalRight();
		break;

	case InStrobExtraPor2:
		emit SetStrobFinalExtraPor2();
		break;

	case InStrobExtraPor3:
		emit SetStrobFinalExtraPor3();
		break;

	case InVRChPoint:
		emit SetVRChPointFinalPos();
		break;

	default: ;
	}
}

int OscillogramPlotterSetter::CalculateCurrOscBeg()
{
	float koeff  = ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F) / width;
	int NewOscBegin = Refference_osc_par.curr_beg_r - (curr_x - drag_start_x)*koeff;

	if(NewOscBegin < 0)
		NewOscBegin = 0;

	return NewOscBegin;
}

int OscillogramPlotterSetter::CalculateCurrOscEnd()
{
	float koeff  = ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F) / width;

	int NewOscEnd = Refference_osc_par.curr_beg_r - (curr_x - drag_start_x)*koeff + ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F);

	if(NewOscEnd < 0)
		NewOscEnd = 0;

	return NewOscEnd;
}

int OscillogramPlotterSetter::CalculateCurrStrobLen()
{
	float koeff  = ((Refference_osc_par.curr_stp_r + 1) * (LEN_OSC - 1) * STEP_KOEF * TEN_F) / width;

	int len = Refference_us_par.strb[_curr_strob].len + koeff * (curr_x - drag_start_x);

	if(len < 0)
		len = 0;

	return len;
}
