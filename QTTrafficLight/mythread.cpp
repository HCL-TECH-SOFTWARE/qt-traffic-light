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
    if(argcnt > 1) // Cmd-line args provided (e.g. to use model debugging). Pass them on to the TargetRTS.
    {
        RTMain::entryPoint( argcnt, argvv );
    }
    else // No cmd-line args provided (e.g. running from Qt Creator). Use default args for a non-debug run.
    {
        const char* argv1[2];
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

void MyThread::walk()
{
    emit MyThread::Instance().OnWalk();
}

void MyThread::stop()
{
    emit MyThread::Instance().OnStop();
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
