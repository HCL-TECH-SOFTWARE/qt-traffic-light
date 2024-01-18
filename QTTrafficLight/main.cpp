#include "mainwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir exeDir(QCoreApplication::applicationDirPath());
    std::string imageDir = exeDir.filePath("../../QTTrafficLight/images").toStdString();

    MainWindow w(argc, argv, imageDir);
    w.resize(150, 400);
    w.show();

    return a.exec();
}
