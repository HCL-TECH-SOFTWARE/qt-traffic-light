#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MainWindow w(argv[0]);
    MainWindow w(argc, argv);
    w.resize(150, 400);
    w.show();

    return a.exec();
}
