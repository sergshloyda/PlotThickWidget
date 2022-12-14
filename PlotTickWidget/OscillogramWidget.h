#pragma once
#include "widgetwithmouseproc.h"
#include "devicesettings.h"
class OscillogramWidget :
	public WidgetWithMouseProc
{
	Q_OBJECT
public:
	OscillogramWidget(QWidget *parent=0, Qt::WindowFlags f=0);
	OscillogramWidget(DeviceSettings* devSettings, QWidget *parent=0, Qt::WindowFlags f=0);
	virtual ~OscillogramWidget(void);
		virtual void createConnection() override;
		void UpdatePlotter();
		void SetCoefficients();
	public	slots:
		void BegOscIntermedChange(int beg);
		void BegOscFinalChange();
		void EndOscIntermedChange(int end);
		void EndOscFinalChange();

		void SetStrobIntermedPos(int strob, int begin, int porog);
		void SetStrobSelected(int strob);
		void SetStrobFinalPos();
		void SetStrobIntermedLeft(int strob, int begin, int len);
		void SetStrobFinalLeft();
		void SetStrobIntermedRight(int strob, int len);
		void SetStrobFinalRight();
		void SetStrobIntermedExtraPor2(int porog);
		void SetStrobFinalExtraPor2();
		void SetStrobIntermedExtraPor3(int porog);
		void SetStrobFinalExtraPor3();

		void SetVRChPointSelected(int point);
		void SetVRChPointIntermedChange(int point, int KUS, int time);
		void SetVRChPointFinalPos();

		void change_AxisXcapt(bool);
		void change_LogCaption(bool);
	signals:
		void change_curr_strob();
		void change_strob_length();
		void change_strob_porog();
		void change_strob_porog2();
		void change_strob_porog3();
		void change_strob_begin();
		void change_osc_range();
		void change_num_p_VRCH();
		void change_param_p_VRCH();
private:
	DeviceSettings* _deviceSettings;
};

