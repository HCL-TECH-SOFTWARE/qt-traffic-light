#include "mainwindow.h"
#include "trafficLightLayout.h"
#include "mythread.h"
#include <QGridLayout>

MainWindow::MainWindow(int argc, char** argv, QWidget *parent)
    : QMainWindow(parent)
{
    setup();
    MyThread::Instance().argcnt = argc;
    MyThread::Instance().argvv = argv;
    MyThread::Instance().start();

    connect(&MyThread::Instance(), SIGNAL(OnRedLight()), this, SLOT(TurnOnRedLight()));
    connect(&MyThread::Instance(), SIGNAL(OnYellowLight()), this, SLOT(TurnOnYellowLight()));
    connect(&MyThread::Instance(), SIGNAL(OnGreenLight()), this, SLOT(TurnOnGreenLight()));
    connect(mButton, SIGNAL(clicked()), this, SLOT(onButtonClicked()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::TurnOnRedLight()
{
    widget.turnOffGreen();
    widget.turnOffYellow();
    widget.turnOnRed();
}

void MainWindow::TurnOnYellowLight()
{
    widget.turnOffGreen();
    widget.turnOffRed();
    widget.turnOnYellow();
}

void MainWindow::TurnOnGreenLight()
{
    widget.turnOffRed();
    widget.turnOffYellow();
    widget.turnOnGreen();
}

void MainWindow::setup()
{
    QWidget *mainWidget = new QWidget();
    mButton  = new QPushButton("Pedestrian wants to cross", this);
    mButton->setFixedSize(QSize(150,50));
    QGridLayout *glayout = widget.getTrafficLightLayout();
    glayout->addWidget(mButton);
    mainWidget->setLayout(glayout);
    setCentralWidget(mainWidget);
}

void MainWindow::onButtonClicked()
{
    MyThread::Instance().pushButtonClicked();
}
