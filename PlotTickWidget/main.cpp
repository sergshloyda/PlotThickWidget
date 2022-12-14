#include "plottickwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PlotTickWidget w;
	w.show();
	return a.exec();
}
