#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen splash(QPixmap(":/JLUlogo.jpeg"));
    splash.show();

    QTime dieTime = QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

    MainWindow w;
    w.show();
    splash.close();
    return a.exec();
}
