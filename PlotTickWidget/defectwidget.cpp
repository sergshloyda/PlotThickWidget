#include "defectwidget.h"
#include"element_info.h"
#include "qapplication.h"
DefectWidget::DefectWidget(QWidget *parent)
	: QWidget(parent)
{
	_deviceSettings = qApp->property("DeviceSettings").value<DeviceSettings*>();
}

DefectWidget::~DefectWidget()
{

}
void DefectWidget::setNumChan(const quint8 nChan)
{
	_nChan=nChan;
}
quint8 DefectWidget::getNumChan() const
{
	return _nChan;
}
void DefectWidget::paintEvent(QPaintEvent * paint_event)
{
	QPainter painter(this);

	QRect cr=paint_event->rect();
	painter.fillRect(cr,Qt::white);
	QRect plotter_wdg_rect=cr;
	painter.drawRect(plotter_wdg_rect);
	painter.setRenderHint(QPainter::Antialiasing, true);
	PlotDefect(painter,plotter_wdg_rect,_nChan);

}
void DefectWidget::PlotDefect(QPainter & painter, const QRect& content_rect,const quint8 chan)
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