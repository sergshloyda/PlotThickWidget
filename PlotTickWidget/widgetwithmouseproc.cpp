#include "widgetwithmouseproc.h"
#include <QEvent>
#include <QMouseEvent>
#include <QTouchEvent>


WidgetWithMouseProc::WidgetWithMouseProc(QWidget *parent, Qt::WindowFlags f)
					: PlotterWidget(parent, f),
					pTester(nullptr),
					touch_on(false)
{
	setAttribute(Qt::WA_AcceptTouchEvents);
	setMouseTracking(true);
}


WidgetWithMouseProc::WidgetWithMouseProc(QWidget *parent, PositionTesterPlotter *tester, Qt::WindowFlags f)
					: PlotterWidget(parent, static_cast<AbstactPlotter *>(tester), f),
					pTester(tester),
					touch_on(false)
{
	setAttribute(Qt::WA_AcceptTouchEvents);
	setMouseTracking(true);
}

WidgetWithMouseProc::~WidgetWithMouseProc()
{
	pTester = nullptr;
}


bool WidgetWithMouseProc::event(QEvent * event)
{
	bool reassept_event = false;

	switch(event->type())
	{
	case QEvent::TouchBegin:
		if(pTester != nullptr)
		{
			QTouchEvent *p_touch_event = reinterpret_cast<QTouchEvent *>(event);
			const QList<QTouchEvent::TouchPoint> &point_list = p_touch_event->touchPoints();


			pTester->TestNewPosition(point_list[0].pos());

			if(pTester->IsCursorChanged())
			{
				setCursor(pTester->GetCursor());
				pTester->CursorAccepted();
			}

			if(!touch_on)
			{
				touch_on = true;
				pTester->SetDragging(true);
			}

			reassept_event = true;
		}
		break;

	case QEvent::TouchUpdate:
		if(pTester != nullptr)
		{
			QTouchEvent *p_touch_event = reinterpret_cast<QTouchEvent *>(event);
			const QList<QTouchEvent::TouchPoint> &point_list = p_touch_event->touchPoints();
			
			pTester->TestNewPosition(point_list[0].pos());
			if(pTester->IsCursorChanged())
			{
				setCursor(pTester->GetCursor());
				pTester->CursorAccepted();
			}

			if(!touch_on)
			{
				touch_on = true;
				pTester->SetDragging(true);
			}

			reassept_event = true;
		}
		break;

	case QEvent::TouchCancel:
	case QEvent::TouchEnd:
		if(pTester != nullptr)
		{	
			if(touch_on)
			{
				touch_on = false;
				pTester->SetDragging(false);
			}
			reassept_event = true;
		}
		break;

	default:;
	}

	bool result = PlotterWidget::event(event);
	if(reassept_event)
		event->accept();
	return result;
}


void WidgetWithMouseProc::mouseMoveEvent(QMouseEvent * event)
{
	PlotterWidget::mouseMoveEvent(event);

	if(pTester != nullptr)
	{
		pTester->TestNewPosition(event->localPos());

		if(pTester->IsCursorChanged())
		{
			setCursor(pTester->GetCursor());
			pTester->CursorAccepted();
		}
	}
}

void WidgetWithMouseProc::mousePressEvent(QMouseEvent * event)
{
	PlotterWidget::mousePressEvent(event);

	if(pTester != nullptr && event->button() == Qt::LeftButton)
	{
		if(!touch_on)
		{
			pTester->SetDragging(true);
			touch_on = true;
		}
	}
}

void WidgetWithMouseProc::mouseReleaseEvent(QMouseEvent * event)
{
	PlotterWidget::mouseReleaseEvent(event);

	if(pTester != nullptr && event->button() == Qt::LeftButton)
	{
		if(touch_on)
		{
			pTester->SetDragging(false);
			touch_on = false;
		}
	}
}

void WidgetWithMouseProc::SetPosTester(PositionTesterPlotter *p_Tester)
{
	SetPlotter(static_cast<AbstactPlotter *>(p_Tester));
	pTester = p_Tester;
	pTester->ConnectToWidget(this);
	createConnection();
}
void WidgetWithMouseProc::createConnection()
{
}