#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "trafficLightLayout.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char** argv, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onButtonClicked();
    void TurnOnRedLight();
    void TurnOnYellowLight();
    void TurnOnGreenLight();

private:
    TrafficLightLayout widget;
    QPushButton *mButton;

    void setup();
};
#endif // MAINWINDOW_H
