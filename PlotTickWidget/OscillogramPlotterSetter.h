#pragma once

//#include "params.h"

#include "dev_interf.h"
#include "dev_struct.h"
#include "OscillogramProperties.h"
#include "positiontesterplotter.h"

//#include <QVector>

#define MAX_FLOAT_OSC 255.0f

#define STEP_KOEF 0.05f		
#define TEN_F  10.0f
class PlotTickWidget;

class OscillogramPlotterSetter : public PositionTesterPlotter
{

Q_OBJECT

protected:

	bool AnyReceived;

	int width;
	int height;

	float x_b;
	float y_b;

	float x_step;
	float y_step;





	int x_sign_step;
	int y_sign_step;

	int frame_width;

	int font_size;

	int ArrowDim;
	int ArrowIndent;
	int ArrowInterval;

	int StrobSetHeight;


	int VRChPtRadius;
	int VRChPtCrossDim;
	int VRChPtIndent;


	bool setted_koefficients;


	OscillogramProperties *OscProp;


	//bool *p_en_set_params;
	PlotTickWidget* _main_widget;


	float *p_sub_thick;
	amp_us_struct_t *p_us_times;


	osc_struct_t Old_ehogr_struct;

	par_osc_t Old_osc_par;
	par_us_t Old_us_par;
	cn_info_t Old_cn_info_par;
	view_cn_info_t Old_view_cn_par;


	par_osc_t Refference_osc_par;
	par_us_t Refference_us_par;
	cn_info_t Refference_cn_info_par;

	int _curr_strob;

	enum cursor_area {
		Outside = 0,

		InBeginOsc = 1,
		InEndOsc = 2,

		InStrobLeft = 3,
		InStrobMiddle = 4,
		InStrobRight = 5,

		InStrobExtraPor2 = 6,
		InStrobExtraPor3 = 7,

		InVRChPoint = 8,

		InAxisX = 9,
		InAxisY = 10

	}  curr_area;

	

	int selected_vrch_point;


/*	bool *p_plot_ogib;
	quint8 *ogib;
*/

//	QVector<QPoint> beam_line;


	 void DrawGrid(QPainter &);
	 void PlotRespond(QPainter & painter,
							const osc_struct_t &curr_ehogr, 
							const par_osc_t &curr_osc_par, 
							const par_us_t &curr_us_par, 
							const cn_info_t &cn_info_par, 
							const view_cn_info_t &curr_view_cn_par);


	 void OutFrameText(QPainter & painter, const QString & string, const int x_rightMid, const int y_rightMid, const int size, const int legth);

	 void PlotVerticalSignature(QPainter & painter);
	 void PlotVerticalSignatureRadio(QPainter & painter);
	 void PlotLogarithmicVerticalSignature(QPainter & painter, const quint8 curr_porog);

	 void PlotHorizontalSignature(QPainter & painter, const par_osc_t &curr_osc_par, const cn_info_t &cn_info_par, const view_cn_info_t &curr_view_cn_par);


	 void PlotStrob(QPainter & painter, const float koeff, float s_begin, float s_end, const float porog1, QColor color, const bool selected, const bool stipple = false);
	 void PlotStrobArrow(QPainter & painter, const float x0, const float y0, const bool left);
	 void PlotStrobSetEnd(QPainter & painter, const float x0, const float y0);



	 float GetVRChPorog(const par_vrch_t &vrch_pars, const quint8 i, const quint8 tact_kUs) const;
	 void PlotVRChPoint(QPainter & painter, const QPen &base_pen, const QPen &point_pen, const QBrush &pointBrush, const QPoint &point);
	 void PlotVRChSelectedPoint(QPainter & painter, const QPen &base_pen, const QPoint &point);

	 void PlotVRChLine(	QPainter & painter, 
								const QPen &base_pen, 
								const QPen &point_pen, 
								const QBrush &pointBrush, 
								const float x1, 
								const float y1, 
								const float x2, 
								const float y2,
								const bool plot_point,
								const bool selected_point);

	 void PlotVRChVerticalSignature(QPainter & painter, const quint8 tact_kUs);


	 void PlotVRCh(QPainter & painter, 
							const float koeff, 
							const par_osc_t &curr_osc_par, 
							const par_us_t &curr_us_par);


	 void PlotUsTimes(QPainter & painter, const float koeff, const float OscBegin);



/*	inline void PlotThickLine(	QPainter & painter, 
								float koeff,
								const float cos_alpha,
								const par_dop_t &par_dop, 
								const par_us_t &uss);
*/



	 bool IsInsidePlot(const float x, const float y) const;
	 bool IsInsideBeginOsc(const float x, const float y) const;
	 bool IsInsideEndOsc(const float x, const float y) const;

	 bool IsInsideAxisX(const float x, const float y) const;
	 bool IsInsideAxisY(const float x, const float y) const;



	 bool IsInsideStrobVisible(const float koeff, const float s_begin, const float s_end) const;

	 bool IsInsideStrobLeft(const float koeff, const float s_begin, const float s_end, const float s_porog, const float x, const float y) const;
	 bool IsInsideStrobMiddle(const float koeff, const float s_begin, const float s_end, const float s_porog, const float x, const float y) const;
	 bool IsInsideStrobRight(const float koeff, const float s_begin, const float s_end, const float s_porog, const float x, const float y) const;

	 bool IsInsideVRChPoint(const int i, const float koeff, const float x, const float y) const;



	virtual void DragStarted() override;
	virtual void DragEnded() override;






	 int CalculateCurrOscBeg();
	 int CalculateCurrOscEnd();
	 int CalculateCurrStrobLen();


public:

	bool vrch_relative_mode;


	OscillogramPlotterSetter(	QObject *refferece_obj, 
								OscillogramProperties *p_OscProp, 
								/*bool *tp_en_set_params,*/
								float *tp_sub_thick, 
								amp_us_struct_t *tp_us_times/*, 
								bool * tp_plot_ogib, 
								quint8 * t_ogib*/);
	virtual ~OscillogramPlotterSetter();

	OscillogramPlotterSetter(/*bool* tp_en_set_params,*/float *tp_sub_thick,amp_us_struct_t *tp_us_times,QObject *parent);
	virtual QRect & SetPlotRect(const QRect &) override;
	void ResetPlot();

	void PaintBackground();
	void PlotRespond(const osc_struct_t &curr_ehogr, const par_osc_t &curr_osc_par, const par_us_t &curr_us_par, const cn_info_t &cn_info_par, const view_cn_info_t &curr_view_cn_par);



	virtual void TestNewPosition(const QPointF &rel_pos) override;


	void SetCoefficients();


signals:

	void BegOscIntermedChange(int new_beg);
	void BegOscFinalChange();
	void EndOscIntermedChange(int new_end);
	void EndOscFinalChange();


	void OscAxisXChange();
	void OscAxisYChange();


	void SetStrobSelected(int strob);
	void SetStrobIntermedPos(int strob, int begin, int porog);
	void SetStrobFinalPos();
	void SetStrobIntermedLeft(int strob, int begin, int len);
	void SetStrobFinalLeft();
	void SetStrobIntermedRight(int strob, int len);
	void SetStrobFinalRight();


	void SetStrobIntermedExtraPor2(int porog);
	void SetStrobFinalExtraPor2();
	void SetStrobIntermedExtraPor3(int porog);
	void SetStrobFinalExtraPor3();



	void SetBScanIntermedPos(int begin, int porog);
	void SetBScanFinalPos();
	void SetBScanIntermedLeft(int begin, int count);
	void SetBScanFinalLeft();
	void SetBScanIntermedRight(int count);
	void SetBScanFinalRight();





	void SetVRChPointSelected(int point);
	void SetVRChPointIntermedChange(int point, int KUS, int time);
	void SetVRChPointFinalPos();


};