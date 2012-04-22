#include <QtGui/QApplication>
#include <ctime>
#include <cstdlib>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
	srand(time(NULL));

    QApplication a(argc, argv);
    MainWindow w;
	w.setPC(argc,argv);
    w.show();

    return a.exec();
}
