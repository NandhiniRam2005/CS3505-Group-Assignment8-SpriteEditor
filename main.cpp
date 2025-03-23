#include "mainwindow.h"
#include "mainmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainModel m;
    MainWindow w(&m);
    w.show();
    return a.exec();
}
