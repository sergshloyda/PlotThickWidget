#pragma once

#include <QColor>
#include"dev_struct.h"
//#include "params.h"


class OscillogramProperties
{
public:

	QColor BackgroundColor;
	QColor OscillogramColor;
	QColor GridColor;
	QColor TextColor;
	QColor VRChColor;
	QColor OgibColor;

	QColor StrobsColor[NUM_STRBS];
	QColor ThickColor;
	QColor AKFillColor;
	QColor LaminationColor;

	QColor MarkerColor;


	QColor AreaColor[2]; // цвета продольных и поперечных дефектов

	QColor IncorrectColor[5];

	QColor FlawColor[5];


	int row_number;
	int column_number;


	float OscillogramWidth;
	int StrobWidth;


	bool logarithm_caption;

	QColor SepLineColor;


	QColor SufficientConditins;
	QColor Error;

	QColor MnemoBackground;
	QColor ThickStrobAmpl;
	

	OscillogramProperties();
	virtual ~OscillogramProperties();	

};
Q_DECLARE_METATYPE(OscillogramProperties*);
