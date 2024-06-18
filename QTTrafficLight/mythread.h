#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "IPushButton.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    static MyThread& Instance() {
        static MyThread inst;
        return inst;
    }
    explicit MyThread(QObject *parent = nullptr);
    void run();
    static void redLight();
    static void yellowLight();
    static void greenLight();
    static void walk();
    static void stop();
    static void pushButtonClicked();
    static void registerPushButton(IPushButton *p);
    virtual ~MyThread(){}
    static char** argvv;
    int argcnt;

signals:
    void OnRedLight();
    void OnGreenLight();
    void OnYellowLight();
    void OnWalk();
    void OnStop();

private:
    static IPushButton* myPushButton;
};

#endif // MYTHREAD_H
