#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include "PushButton.h"

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
    static void pushButtonClicked();
    static void registerPushButton(PushButton_Actor *p);
    virtual ~MyThread(){}
    static char** argvv;
    int argcnt;

signals:
    void OnRedLight();
    void OnGreenLight();
    void OnYellowLight();

private:
    static PushButton_Actor* myPushButton;
};

#endif // MYTHREAD_H
