#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Python.h>
#include <QMainWindow>
#include <QFileDialog>
#include <QString>
#include <QToolButton>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QListWidgetItem>
#include <QProcess>
#include <QTimer>
#include <QThread>
#include <QSettings>

#include <cstdio>
#include <cstring>

#include "mythread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    FILE *fpin;
    MyThread *BashThread;
    QTimer *BashTimer;
    QThread *WorkThread;
    Dummy dummy;
    QSettings* MySetting;

private slots:
    void selectPath();
    void getParamList();
    void saveChange();
    void referencePath();
    void pythonFilePath();
    void currentPathDic();
    void plotPath();
    void roslaunchFile();
    void roslaunchStopFile();
    void RefreshBashMessage();
    void shellSelect();
};
#endif // MAINWINDOW_H
