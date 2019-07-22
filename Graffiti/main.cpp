#include "Graffiti.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Graffiti w;
	w.show();
	return a.exec();
}
