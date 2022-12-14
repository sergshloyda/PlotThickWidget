#include "AbstactPlotter.h"


AbstactPlotter::AbstactPlotter(QObject *parent) :
				QObject(parent),
				pixmap_width(0),
				pixmap_height(0),
				WidthUpStep(1),
				HeightUpStep(1),
				NeedResize(false),
				left(0),
				top(0),
				default_colour(Qt::white),
				pixmap(nullptr),
				PosRect(),
				multithread_mode(false),
				MainPlotWidget(nullptr)
{
}

AbstactPlotter::~AbstactPlotter(void)
{
	if(pixmap != nullptr)
	{
		delete pixmap;
		pixmap = nullptr;
	}

	MainPlotWidget = nullptr;
}

QRect & AbstactPlotter::SetPlotRect(const QRect &fullRect)
{
	NeedResize = false;

	if( (fullRect.width() - pixmap_width) > WidthUpStep )
	{
		pixmap_width = fullRect.width(); 
		NeedResize = true;
	} 
	else if( fullRect.width() < pixmap_width )
	{
		pixmap_width = fullRect.width() - WidthUpStep; 
		NeedResize = true;
	}

	if( (fullRect.height() - pixmap_height) > HeightUpStep )
	{
		pixmap_height = fullRect.height();
		NeedResize = true;
	}
	else if(fullRect.height() < pixmap_height)
	{
		pixmap_height = fullRect.height() - HeightUpStep;
		NeedResize = true;
	}

	left = (fullRect.width() - pixmap_width)/2;
	top = (fullRect.height() - pixmap_height)/2;

	PosRect.setRect( left, top, pixmap_width, pixmap_height);

	if(!NeedResize)
		return PosRect;

	if(pixmap!= nullptr)
	{
		delete pixmap;
		pixmap = nullptr;
	}
	pixmap = new QPixmap( pixmap_width,pixmap_height);
	pixmap->fill(default_colour);
	return PosRect;
}

QPixmap * AbstactPlotter::GetPixmap()
{
	return pixmap;
}

void AbstactPlotter::ConnectToWidget(QWidget *MainPlotWidgetNew)
{
	MainPlotWidget = MainPlotWidgetNew;
}

void AbstactPlotter::UpdatePlot()
{
	if(MainPlotWidget != nullptr)
		MainPlotWidget->update();
}



const volatile bool &AbstactPlotter::IsMultithread() const
{
	return multithread_mode;
}


bool AbstactPlotter::LockPixmap()
{
	return true;
}

void AbstactPlotter::UnlockPixmap()
{
}

void AbstactPlotter::SetDefaultColor(const QColor &new_default_colour)
{
	default_colour = new_default_colour;
}
