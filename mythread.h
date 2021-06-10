#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QDebug>
#include <cstdio>
#include <cstring>
#include <QThread>
#include "signal.h"

class Dummy:public QObject
{
    Q_OBJECT
public:
    Dummy(QObject* parent=0):QObject(parent)     {}
public slots:
    void emitsig()
    {
        emit sig();
    }
    void emitstop()
    {
        emit stopsig();
    }
signals:
    void sig();
    void stopsig();
};

class MyThread : public QObject
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    void setBash(QString bashline);

    FILE *getFilePope();
    void MyThreadClose();
signals:


private:
    QString BashLine;
    FILE* RosLaunchFile;
    int PID;
    Qt::HANDLE MyThreadId;
public slots:
    void run();

};

#endif // MYTHREAD_H
