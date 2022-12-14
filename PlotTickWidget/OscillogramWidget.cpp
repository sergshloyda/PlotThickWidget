#include "OscillogramWidget.h"
#include "OscillogramPlotterSetter.h"
#include "qdebug.h"

OscillogramWidget::OscillogramWidget(QWidget *parent, Qt::WindowFlags f):
WidgetWithMouseProc(parent,f)
{
}
OscillogramWidget::OscillogramWidget(DeviceSettings* devSettings, QWidget *parent, Qt::WindowFlags f):
WidgetWithMouseProc(parent,f),_deviceSettings(devSettings)
{
	
}

OscillogramWidget::~OscillogramWidget(void)
{
}
void OscillogramWidget::createConnection()
{
	
	connect(pTester, SIGNAL(SetStrobSelected(int)), this, SLOT(SetStrobSelected(int)));
	connect(pTester, SIGNAL(BegOscIntermedChange(int)), this, SLOT(BegOscIntermedChange(int)));
	connect(pTester, SIGNAL(BegOscFinalChange()), this, SLOT(BegOscFinalChange()));
	connect(pTester, SIGNAL(EndOscIntermedChange(int)), this, SLOT(EndOscIntermedChange(int)));
	connect(pTester, SIGNAL(EndOscFinalChange()), this, SLOT(EndOscFinalChange()));

	connect(pTester, SIGNAL(SetStrobIntermedPos(int, int, int)), this, SLOT(SetStrobIntermedPos(int, int, int)));
	connect(pTester, SIGNAL(SetStrobFinalPos()), this, SLOT(SetStrobFinalPos()));
	connect(pTester, SIGNAL(SetStrobIntermedLeft(int, int, int)), this, SLOT(SetStrobIntermedLeft(int, int, int)));
	connect(pTester, SIGNAL(SetStrobFinalLeft()), this, SLOT(SetStrobFinalLeft()));
	connect(pTester, SIGNAL(SetStrobIntermedRight(int, int)), this, SLOT(SetStrobIntermedRight(int, int)));
	connect(pTester, SIGNAL(SetStrobFinalRight()), this, SLOT(SetStrobFinalRight()));


	connect(pTester, SIGNAL(SetStrobIntermedExtraPor2(int)), this, SLOT(SetStrobIntermedExtraPor2(int)));
	connect(pTester, SIGNAL(SetStrobFinalExtraPor2()), this, SLOT(SetStrobFinalExtraPor2()));
	connect(pTester, SIGNAL(SetStrobIntermedExtraPor3(int)), this, SLOT(SetStrobIntermedExtraPor3(int)));
	connect(pTester, SIGNAL(SetStrobFinalExtraPor3()), this, SLOT(SetStrobFinalExtraPor3()));

#if 0

	connect(pTester, SIGNAL(SetBScanIntermedPos(int, int)), this, SLOT(SetBScanIntermedPos(int, int)));
	connect(pTester, SIGNAL(SetBScanFinalPos()), this, SLOT(SetBScanFinalPos()));
	connect(pTester, SIGNAL(SetBScanIntermedLeft(int, int)), this, SLOT(SetBScanIntermedLeft(int, int)));
	connect(pTester, SIGNAL(SetBScanFinalLeft()), this, SLOT(SetBScanFinalLeft()));
	connect(pTester, SIGNAL(SetBScanIntermedRight(int)), this, SLOT(SetBScanIntermedRight(int)));
	connect(pTester, SIGNAL(SetBScanFinalRight()), this, SLOT(SetBScanFinalRight()));
#endif



	connect(pTester, SIGNAL(SetVRChPointSelected(int)), this, SLOT(SetVRChPointSelected(int)));
	connect(pTester, SIGNAL(SetVRChPointIntermedChange(int, int, int)), this, SLOT(SetVRChPointIntermedChange(int, int, int)));
	connect(pTester, SIGNAL(SetVRChPointFinalPos()), this, SLOT(SetVRChPointFinalPos()));

#if 0
	connect(pTester, SIGNAL(OscAxisXChange()), this, SLOT(OscAxisXChange()));
	connect(pTester, SIGNAL(OscAxisYChange()), this, SLOT(OscAxisYChange()));
#endif
}

void OscillogramWidget::UpdatePlotter()
{
	const par_osc_t &osc_par = _deviceSettings->getViewParOsc();
	OscillogramPlotterSetter* osc_plotter=static_cast<OscillogramPlotterSetter*>(pTester);
	osc_struct_t curr_echogr;
	memset(&curr_echogr,0,sizeof(osc_struct_t));
	osc_plotter->PlotRespond(curr_echogr,osc_par,_deviceSettings->getSelChanAmplifier(),_deviceSettings->getSelChanInfo(),_deviceSettings->getSelChanViewInfo());
}

void OscillogramWidget::SetCoefficients()
{
	
	OscillogramPlotterSetter* osc_plotter=static_cast<OscillogramPlotterSetter*>(pTester);

	osc_plotter->SetCoefficients();
}
void OscillogramWidget::SetStrobIntermedPos(int strob, int begin, int porog)

{
	bool strob_change=false;
	if(_deviceSettings->getOscCurrStrobNum()!=strob)
		strob_change=true;
	_deviceSettings->setOscCurrStrob(strob);

	_deviceSettings->setOscCurrStrobBegin(begin);
	_deviceSettings->setOscCurrStrobLevel(porog);
	if(_deviceSettings->getOscCurrStrobExtraPorSetted())
	{
		
		_deviceSettings->setOscCurrStrobSubLevel();
	}
	

	if(strob_change)
		emit change_curr_strob();
	else
	{
		emit change_strob_begin();
		emit change_strob_porog();
	}
#if 0
	if(extra_por_setted())
		set_sub_extra_por();
#endif

	UpdatePlotter();
}

void  OscillogramWidget::SetStrobSelected(int strob)
{
	
	

	if(_deviceSettings->getOscCurrStrobNum()!=strob)
	{
		_deviceSettings->setOscCurrStrob(strob);
		_deviceSettings->setSelChanViewInfoCurrStrob(strob);
		UpdatePlotter();
		emit change_curr_strob();
			
	}
}

void OscillogramWidget::BegOscIntermedChange(int beg)
{
	if(beg < MIN_BEGR)
		beg = MIN_BEGR;
	if(beg > MAX_BEGR)
		beg = MAX_BEGR;

		_deviceSettings->setOscBegRange(beg);

	emit change_osc_range();

	UpdatePlotter();
}
void OscillogramWidget::BegOscFinalChange()
{

	_deviceSettings->setDeviceChangedParams(CHNG_BEGR);
	const par_osc_t &osc_par = _deviceSettings->getViewParOsc();
	_deviceSettings->setSelChanViewInfoBegRange(osc_par.curr_beg_r);

}

void OscillogramWidget::EndOscIntermedChange(int end)
{
	if(end < MIN_ENDR)
		end = MIN_ENDR;
	if(end > MAX_ENDR)
		end = MAX_ENDR;
	_deviceSettings->setOscEndRange(end);

	emit change_osc_range();

	UpdatePlotter();
}

void OscillogramWidget::EndOscFinalChange()
{
	_deviceSettings->setDeviceChangedParams(CHNG_ENDR);
	const par_osc_t &osc_par = _deviceSettings->getViewParOsc();
	_deviceSettings->setSelChanViewInfoStepRange(osc_par.curr_stp_r);
}
void OscillogramWidget::SetStrobFinalPos()
{
	if(_deviceSettings->getOscCurrStrobExtraPorSetted())
	{
		bool main_strob_change = false;
		bool extra_strobs_change = false;
		_deviceSettings->correctOscCurrStrobLevel(0,&main_strob_change,&extra_strobs_change);
		if(main_strob_change)
		{
		
			emit change_strob_porog();
			_deviceSettings->setDeviceChangedParams(CHNG_POR);
		}
		if(extra_strobs_change)
		{
			emit change_strob_porog2();
			emit change_strob_porog3();
		
		}
		_deviceSettings->setOscCurrStrobSubLevel();

		if(main_strob_change || extra_strobs_change)
			UpdatePlotter();

	}
	//update_all_rows();

	_deviceSettings->setDeviceChangedParams(CHNG_BSTRB | CHNG_POR);

}
void OscillogramWidget::SetStrobIntermedLeft(int strob, int begin, int len)
{
	bool strob_change=false;
	if(_deviceSettings->getOscCurrStrobNum()!=strob)
		strob_change=true;
	_deviceSettings->setOscCurrStrob(strob);

	_deviceSettings->setOscCurrStrobBegin(begin);
	_deviceSettings->setOscCurrStrobLen(len);
	
	if(strob_change)
	{
		
		emit change_curr_strob();
	}
	else
	{
		emit change_strob_begin();
		emit change_strob_length();
	
	}

	UpdatePlotter();
}

void OscillogramWidget::SetStrobFinalLeft()
{
	
	_deviceSettings->setDeviceChangedParams(CHNG_BSTRB | CHNG_LSTRB);

}

void OscillogramWidget::SetStrobIntermedRight(int strob, int len)
{
	bool strob_change=false;
	if(_deviceSettings->getOscCurrStrobNum()!=strob)
		strob_change=true;
	_deviceSettings->setOscCurrStrob(strob);

	_deviceSettings->setOscCurrStrobLen(len);

	if(strob_change)
	{
		
		emit change_curr_strob();
	}
	else
	{
		emit change_strob_length();
	
	}

	UpdatePlotter();
}

void OscillogramWidget::SetStrobFinalRight()
{

	_deviceSettings->setDeviceChangedParams(CHNG_LSTRB);
	
}
void OscillogramWidget::SetStrobIntermedExtraPor2(int porog)
{

	_deviceSettings->setOscCurrStrobExtraLevel_2(porog);

	
	emit change_strob_porog2();
	_deviceSettings->setOscCurrStrobSubLevel();

	UpdatePlotter();
}

void OscillogramWidget::SetStrobFinalExtraPor2()
{

		bool main_strob_change = false;
		bool extra_strobs_change = false;
		_deviceSettings->correctOscCurrStrobLevel(1,&main_strob_change,&extra_strobs_change);
		if(main_strob_change)
		{
			
			emit change_strob_porog();
			_deviceSettings->setDeviceChangedParams(CHNG_POR);
		}
		if(extra_strobs_change)
		{
			emit change_strob_porog2();
			emit change_strob_porog3();
		
		}
		_deviceSettings->setOscCurrStrobSubLevel();

		if(main_strob_change || extra_strobs_change)
			UpdatePlotter();


	//update_all_rows();

	

}

void OscillogramWidget::SetStrobIntermedExtraPor3(int porog)
{


	_deviceSettings->setOscCurrStrobExtraLevel_3(porog);
	

	emit change_strob_porog3();

	_deviceSettings->setOscCurrStrobSubLevel();

	UpdatePlotter();
}

void OscillogramWidget::SetStrobFinalExtraPor3()
{
	bool main_strob_change = false;
	bool extra_strobs_change = false;
	_deviceSettings->correctOscCurrStrobLevel(2,&main_strob_change,&extra_strobs_change);
	if(main_strob_change)
	{
	
		emit change_strob_porog();
		_deviceSettings->setDeviceChangedParams(CHNG_POR);
	}
	if(extra_strobs_change)
	{
		
		emit change_strob_porog2();
		emit change_strob_porog3();
	}
	_deviceSettings->setOscCurrStrobSubLevel();

	if(main_strob_change || extra_strobs_change)
		UpdatePlotter();


	//update_all_rows();

}


void OscillogramWidget::SetVRChPointSelected(int point)
{

	if(_deviceSettings->getOscCurrVRChPointNum() != point)
	{
		_deviceSettings->setOscCurrVRChPointNum(point);
		_deviceSettings->setDeviceChangedParams(CHNG_NUMPV);
		_deviceSettings->setSelChanViewInfoVRChPointNum(_deviceSettings->getOscCurrVRChPointNum());

		emit change_num_p_VRCH();
		UpdatePlotter();
	}

}

void OscillogramWidget::SetVRChPointIntermedChange(int point, int KUS, int time)
{

	SetVRChPointSelected(point);
	_deviceSettings->setOscAmplVRChPointTime(point,time);
	_deviceSettings->setOscAmplVRChPointKUS(point,KUS);

	DeviceSettings::CheckAndCorrectAllVRChTime(_deviceSettings,false);  

	emit change_param_p_VRCH();
	UpdatePlotter();
}

void OscillogramWidget::SetVRChPointFinalPos()
{

	_deviceSettings->setDeviceChangedParams(CHNG_NUMPV | CHNG_VTIME | CHNG_VKUS);
	_deviceSettings->setSelChanViewInfoVRChPointNum(_deviceSettings->getOscCurrVRChPointNum());
}

void OscillogramWidget::change_AxisXcapt(bool new_axis_x)
{

	for(int i=0;i<NUM_CHANS;i++)
	{
		view_cn_info_t* p_view_cn_info=_deviceSettings->getChanViewInfoPtr(i);
		p_view_cn_info->axis_mode.axis_x_mode=new_axis_x ? 1 : 0;
	}
	UpdatePlotter();
}
void OscillogramWidget::change_LogCaption(bool new_log_capt)
{

		for(int i=0;i<NUM_CHANS;i++)
	{
		view_cn_info_t* p_view_cn_info=_deviceSettings->getChanViewInfoPtr(i);
		p_view_cn_info->axis_mode.axis_y_mode = new_log_capt ? 1 : 0;
	}
	UpdatePlotter();
}