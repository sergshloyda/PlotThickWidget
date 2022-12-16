#ifndef __DRAW_DEFECT_ROW__
#define __DRAW_DEFECT_ROW__
#include "RenderThread.h"
#define NUM_EXTRA_POR NUM_STRBS_EXTRA+1
#define NUM_STROB_AK 0

class DrawDefectRow:public DrawStrategy
{
public:
	DrawDefectRow(quint8 num_chan,DeviceSettings* device_settings);
	virtual ~DrawDefectRow(){}
		
	virtual QImage Draw(int w,int h,const QList<Element_Info*>& list)override;
	virtual QPixmap DrawPixmap(int w,int h, const QList<Element_Info*>& list)override;
private:
	void PlotDefectElement(QPainter& painter,const DefectElement* def_elem, const par_strb_t *strb_par,const par_strb_info_t *strb_chan_info,float curr_x,const float next_x,const float pixmap_height,const float plot_step_y);
	void PlotStrobPorLevel(QPainter & painter,QPen &pen,const QColor &col,QPen &back_pen,const QLineF &line,int &offset);
	void PlotErrorFlags(QPainter & painter,	const quint8 &defect_flag,const float curr_x,const float next_x,const int curr_y_b,const int curr_height);
	void setColors();

	quint8 _num_chan;
	int _beg_index;
	QElapsedTimer _timer;

	QColor _sub_strobs_color[NUM_STRBS][NUM_EXTRA_POR];
	QColor _sufficient_condition_color;
	QColor _ak_fill_color;
	QColor _error_flag_incorrect_color;
	QColor _error_flag_data_skip_color;
	QColor _error_flag_no_ak_color;
	QColor _error_flag_lamination_color;

	bool _prev_filled;
	quint8 _prev_strob_ak_level;

	static const int line_width=1;
	static const int AK_line_width=2;

};
#endif