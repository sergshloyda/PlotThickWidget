#ifndef LINEEDITRETURN_H
#define LINEEDITRETURN_H

#include <QLineEdit>

class LineEditReturn : public QLineEdit
{
	Q_OBJECT

public:
	LineEditReturn(QWidget *parent);
	~LineEditReturn();
protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* pe);
	void	keyPressEvent(QKeyEvent * pe);
signals:

	void SignalEnterPressed(void);
	
};

#endif // LINEEDITRETURN_H
