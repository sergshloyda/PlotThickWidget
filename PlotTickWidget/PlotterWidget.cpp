#include "PlotterWidget.h"
#include "qpainter.h"
#include <QPaintEvent>


PlotterWidget::PlotterWidget(QWidget *parent, Qt::WindowFlags f) :
								QWidget(parent, f),
								pPlotter(nullptr)
{

}

PlotterWidget::PlotterWidget(QWidget *parent, AbstactPlotter *plotter, Qt::WindowFlags f) :
								QWidget(parent, f),
								pPlotter(plotter)
{
	pPlotter->ConnectToWidget(this);
}

PlotterWidget::~PlotterWidget(void)
{
	pPlotter = nullptr;
}


void PlotterWidget::paintEvent(QPaintEvent *event)
{
	if(pPlotter != nullptr)
	{
		if(pPlotter->IsMultithread())
		{
			if(pPlotter->LockPixmap())
			{
				QPainter painter(this);
				if(painter.isActive())
				{
					QRect cr = contentsRect();
					QRect fr = pPlotter->SetPlotRect(cr);
					QPixmap *pm = pPlotter->GetPixmap();
					painter.drawPixmap( fr, *pm);
				}
				painter.end();
				pPlotter->UnlockPixmap();
			}

			// иначе ничего не рисуем - pixmap не отрисован
		}
		else
		{
			QPainter painter(this);
			if(!painter.isActive())
				return;
			QRect cr = contentsRect();
			QRect fr = pPlotter->SetPlotRect(cr);
			QPixmap *pm = pPlotter->GetPixmap();
			painter.drawPixmap( fr, *pm);
		}
	}
	else
	{
		QRect cRect = event->rect();
		QRect bRect = geometry();

		if(cRect.width() == bRect.width() && cRect.height() == bRect.height())
		{
			QPainter painter(this);
			painter.fillRect(cRect,Qt::white);
	
			painter.setPen(Qt::red);
			painter.drawText(rect(), Qt::AlignCenter, tr("Sorry window policy not set :("));
			return;
    
		}

	}
}

void PlotterWidget::SetPlotter(AbstactPlotter *p_Plotter)
{
	pPlotter = p_Plotter;
}
