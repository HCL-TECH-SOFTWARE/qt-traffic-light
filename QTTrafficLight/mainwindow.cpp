#include "mainwindow.h"
#include "trafficLightLayout.h"
#include "mythread.h"
#include <QGridLayout>
#include <QLabel>
#include <QImage>
#include <QDir>

MainWindow::MainWindow(int argc, char** argv, std::string& imageDir)
    : QMainWindow(nullptr), imageDir(imageDir)
{
    setup();
    MyThread::Instance().argcnt = argc;
    MyThread::Instance().argvv = argv;
    MyThread::Instance().start();

    connect(&MyThread::Instance(), SIGNAL(OnRedLight()), this, SLOT(TurnOnRedLight()));
    connect(&MyThread::Instance(), SIGNAL(OnYellowLight()), this, SLOT(TurnOnYellowLight()));
    connect(&MyThread::Instance(), SIGNAL(OnGreenLight()), this, SLOT(TurnOnGreenLight()));
    connect(&MyThread::Instance(), SIGNAL(OnStop()), this, SLOT(TurnOnStop()));
    connect(&MyThread::Instance(), SIGNAL(OnWalk()), this, SLOT(TurnOnWalk()));
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

void MainWindow::TurnOnStop()
{
    std::string path = imageDir + "/stop.png";
    QPixmap pixMap(path.c_str());
    image->setPixmap(pixMap);
}

void MainWindow::TurnOnWalk()
{
    std::string path = imageDir + "/walk.png";
    QPixmap pixMap(path.c_str());
    image->setPixmap(pixMap);
}

void MainWindow::setup()
{
    QWidget *mainWidget = new QWidget();
    mainWidget->setFixedSize(QSize(350,350));
    mButton  = new QPushButton("Pedestrian wants to cross", this);

    QGridLayout *glayout = widget.getTrafficLightLayout();
    glayout->addWidget(mButton, 1, 1);
    glayout->addWidget(new QLabel("Push the button --->"), 1, 0);
    image = new QLabel();

    std::string path = imageDir + "/stop.png";

    QPixmap pixMap(path.c_str());
    image->setPixmap(pixMap);
    image->setScaledContents(false);
    glayout->addWidget(image, 0, 1);
    mainWidget->setLayout(glayout);
    setCentralWidget(mainWidget);
}

void MainWindow::onButtonClicked()
{    
    MyThread::Instance().pushButtonClicked();
}
