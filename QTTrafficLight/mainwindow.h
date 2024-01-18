#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "trafficLightLayout.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, std::string& imageDir);
    ~MainWindow();

public slots:
    void onButtonClicked();
    void TurnOnRedLight();
    void TurnOnYellowLight();
    void TurnOnGreenLight();
    void TurnOnStop();
    void TurnOnWalk();

private:
    TrafficLightLayout widget;
    QPushButton *mButton;
    QLabel* image;
    std::string imageDir;

    void setup();
};
#endif // MAINWINDOW_H
