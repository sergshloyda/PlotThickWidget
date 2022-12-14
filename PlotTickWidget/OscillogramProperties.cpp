#include "OscillogramProperties.h"


OscillogramProperties::OscillogramProperties() :
				BackgroundColor(Qt::white),
				OscillogramColor(0, 100, 0),
				GridColor(Qt::gray),
				TextColor(Qt::black),
				VRChColor(Qt::darkGreen),
				OgibColor(Qt::darkGray),
				ThickColor(128,64,0),
				AKFillColor(31,255,210),
				LaminationColor(223,173,0),

				MarkerColor(Qt::blue),

				row_number(12),
				column_number(10),

				OscillogramWidth(2.0f),
				StrobWidth(4),

				logarithm_caption(false),

				SepLineColor(70,70,70),

				SufficientConditins(Qt::darkGreen),
				Error(Qt::red),

				MnemoBackground(50,50,210),
				ThickStrobAmpl()	
{
	int hue;
	int strat;
	int value;


	StrobsColor[0] = Qt::darkGray;
	StrobsColor[1] = Qt::red;
	StrobsColor[2] = QColor(160, 0, 255);
	StrobsColor[3] = Qt::blue;

	AreaColor[0] = Qt::red;
	AreaColor[1] = QColor(160, 0, 255);

	IncorrectColor[0] = QColor(230, 230, 230, 160);	// неправильная настройка
	IncorrectColor[1] = QColor(133, 133, 133, 160);	// данные не приняты
	IncorrectColor[2] = QColor(160, 160, 160, 160/*128*/);	// нет сигнала


	IncorrectColor[3] = AKFillColor;		// потеря АК
	IncorrectColor[3].setAlpha(160);

	IncorrectColor[4] = LaminationColor;	// наличие расслоения
	IncorrectColor[4].setAlpha(160);


	StrobsColor[0].getHsv(&hue, &strat, &value);
	ThickStrobAmpl.setHsv(hue, 0.4f*strat, 0.75f*(255-value)+value);



	FlawColor[0] = Error;
	FlawColor[1] = QColor(128, 0, 0);
	FlawColor[2] = Qt::yellow;
	FlawColor[3] = Qt::green;
	FlawColor[4] = QColor(241, 121, 255);

}


OscillogramProperties::~OscillogramProperties()
{
}
