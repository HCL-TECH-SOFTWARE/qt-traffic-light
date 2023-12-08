#include "mythread.h"
#include "RTMain.h"

PushButton_Actor* MyThread::myPushButton = nullptr;
char** MyThread::argvv = nullptr;

MyThread::MyThread(QObject *parent)
    : QThread{parent}
{

}

void MyThread::run()
{
    if(argcnt > 1)// want to use model debugging functionality or pass arg from cmd
    {
        RTMain::entryPoint( argcnt, argvv );
    }
    else//running app from QT IDE
    {
        char* argv1[2];
        argv1[0] =  argvv[0];
        argv1[1] = {"-URTS_DEBUG=quit"};
        RTMain::entryPoint( ++argcnt, argv1 );
    }
}

void MyThread::redLight()
{
    emit MyThread::Instance().OnRedLight();
}

void MyThread::greenLight()
{
    emit MyThread::Instance().OnGreenLight();
}

void MyThread::yellowLight()
{
    emit MyThread::Instance().OnYellowLight();
}

void MyThread::pushButtonClicked()
{
    if(myPushButton)
        myPushButton->onClicked();
}

void MyThread::registerPushButton(PushButton_Actor *p)
{
    myPushButton = p;
}
