#include "mythread.h"
#include "dirent.h"
#include "sys/types.h"

MyThread::MyThread(QObject *parent) : QObject(parent)
{
    RosLaunchFile=NULL;
    PID=0;
}


void MyThread::setBash(QString bashline)
{
    BashLine=bashline;
}

void MyThread::run()
{
    qDebug() << BashLine << Qt::endl;
    qDebug() << "run thread: " << QThread::currentThreadId();
    if(RosLaunchFile==NULL)
        RosLaunchFile = popen(BashLine.toLatin1(), "r");
}

FILE* MyThread::getFilePope()
{
    if(RosLaunchFile!=NULL)
        return RosLaunchFile;
    else
        return NULL;
}

void MyThread::MyThreadClose()
{
    // 查看pclose是否阻塞，为什么不能正常关闭
    qDebug() << "dir is NULL " << Qt::endl;
    popen(BashLine.toLatin1(), "r"); // 再次打开就可以关闭

    pclose(RosLaunchFile); //关闭当前终端正在执行的任务
    qDebug() << "Thread has quit!" << QThread::currentThreadId() << Qt::endl;
    RosLaunchFile=NULL;
}
