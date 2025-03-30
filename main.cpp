#include "mainwindow.h"
#include "mainmodel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    MainModel model;
    MainWindow window(&model);
    window.show();
    return application.exec();
}
