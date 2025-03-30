/*
* Checked by Joel Rodriguez
A class that contaisn the main method to start up teh application.

By Joel Rodriguez, Jacob Anderson,
Adharsh Ramakrishnan, Nandhini Ramanathan
Jake Heairld & Joseph Hamilton

March 30, 2025
*/

#include "mainwindow.h"
#include "mainmodel.h"
#include <QApplication>

/**
 * Main method that initializes the application, creates the model and the main window,
 * and starts the application.
 *
 * @param argc - The number of command-line arguments.
 * @param argv - An array of command-line arguments.
 *
 * @return The exit status of the application.
 */
int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    MainModel model;
    MainWindow window(&model);

    window.show();
    return application.exec();
}
