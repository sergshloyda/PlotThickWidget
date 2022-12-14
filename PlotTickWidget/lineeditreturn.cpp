#include "lineeditreturn.h"
#include <qevent.h>
LineEditReturn::LineEditReturn(QWidget *parent)
	: QLineEdit(parent)
{

}

LineEditReturn::~LineEditReturn()
{

}
void LineEditReturn::mouseDoubleClickEvent(QMouseEvent* pe)
{
	QLineEdit::mouseDoubleClickEvent(pe);
	emit SignalEnterPressed();
}


void LineEditReturn::keyPressEvent(QKeyEvent * pe)
{
	if((pe->key() == Qt::Key_Return) || (pe->key() == Qt::Key_Enter))
		emit SignalEnterPressed();
	else
		QLineEdit::keyPressEvent(pe);
}