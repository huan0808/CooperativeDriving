#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    BashThread = new MyThread();
    WorkThread = new QThread();
    BashThread->moveToThread(WorkThread);

    BashTimer=new QTimer();
    fpin=NULL;
    connect(ui->LaunchSelectButton, SIGNAL(clicked()), this, SLOT(selectPath()));
    ui->paramList->setResizeMode(QListView::Adjust);
    ui->paramList->setAutoScroll(true);
    connect(ui->SaveChangeBtn, SIGNAL(clicked()), this, SLOT(saveChange()));
    connect(ui->CurrentPahtDicBtn, SIGNAL(clicked()), this, SLOT(currentPathDic()));
    connect(ui->PlotPathBtn, SIGNAL(clicked()), this, SLOT(plotPath()));
    connect(ui->ReferencePathBtn, SIGNAL(clicked()), this, SLOT(referencePath()));
    connect(ui->RoslaunchFileBtn, SIGNAL(clicked()), this, SLOT(roslaunchFile()));
    connect(ui->PythonFilePathBtn, SIGNAL(clicked()), this, SLOT(pythonFilePath()));
    connect(ui->RoslaunchStopBtn, SIGNAL(clicked()), this, SLOT(roslaunchStopFile()));
    connect(ui->ShellSelectButton, SIGNAL(clicked()), this, SLOT(shellSelect()));
    connect(ui->ClearButton, SIGNAL(clicked()), ui->LogOutputText, SLOT(clear()));
    QObject::connect(&dummy, SIGNAL(sig()), BashThread, SLOT(run()));

    // 界面内容读取配置文件
    MySetting = new QSettings("mySettings.ini", QSettings::IniFormat);
    QString SectionName = "plot/";
    QString value = MySetting->value(SectionName + "pythonFile").toString();
    ui->PythonFilePathLine->setText(value);
    value = MySetting->value(SectionName + "referenceFile").toString();
    ui->ReferencePathLine->setText(value);
    value = MySetting->value(SectionName + "dataDic").toString();
    ui->CurrentPathDicLine->setText(value);

    SectionName = "launch/";
    value = MySetting->value(SectionName + "launch").toString();
    ui->LaunchPathLine->setText(value);
    value = MySetting->value(SectionName + "shell").toString();
    ui->ShellPathLine->setText(value);
    if(ui->LaunchPathLine->text().size()) // 不为空的情况下
        getParamList();

    this->setWindowIcon(QIcon(":/CTIS.ico"));
//    QPixmap pixmap(":/logo/JLUlogo.jpeg");
//    QPixmap finalmap = pixmap.scaled(ui->LogOutputText->size(),Qt::KeepAspectRatio);
//    QPalette palette=ui->LogOutputText->palette();
//    palette.setBrush(QPalette::Base, QBrush(finalmap));
//    ui->LogOutputText->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getParamList()
{
    QFile launchFile(ui->LaunchPathLine->text().toLatin1().data());
    launchFile.open(QIODevice::ReadWrite);
    QString text;
    QTextStream ts(&launchFile), ts2;
    while (!ts.atEnd()) {
        text=ts.readLine();
        int index = text.indexOf("param");
        if(index!=-1) { // 存在目标字符串
            for (int i=0;i<text.length();++i) {
                if (text[i] == '='){ // 在QListwidget中添加元素
                    // 寻找name和参数值的起止地址
                    int nameStart=0, nameEnd=i;
                    int paramStart=i+2, paramEnd=0;
                    for(int j=nameEnd;j>0;--j)
                        if(text[j]==' '){
                            nameStart=j+1;
                            break;
                        }

                    for(int j=paramStart;j<text.size();++j)
                        if(text[j]=='\"'){
                            paramEnd=j;
                            break;
                        }

                    QString paramname = text.mid(nameStart, nameEnd-nameStart);
                    QString paramvalue = text.mid(paramStart, paramEnd-paramStart);

                    QWidget *wContainer = new QWidget(ui->paramList);
                    QLabel *paramName = new QLabel(paramname);
                    paramName->setObjectName(paramname);
                    QLineEdit *paramValue = new QLineEdit(paramvalue);
                    paramValue->setObjectName(paramvalue);

                    QGridLayout *listGrid = new QGridLayout();
                    listGrid->addWidget(paramName, 0, 0);
                    listGrid->addWidget(paramValue, 0, 1);
                    wContainer->setLayout(listGrid);

                    QString tooltip = "参数名称";
                    QListWidgetItem* WContainerItem=new QListWidgetItem(ui->paramList);
                    WContainerItem->setSizeHint(QSize(40,40));
//                    WContainerItem->setToolTip(tooltip + "参数值");
                    ui->paramList->setItemWidget(WContainerItem, wContainer);//将WContainer赋予WContainerItem

                }
            }
        }
    }
    launchFile.close();
}

void MainWindow::selectPath()
{
    ui->paramList->clear();
    QString filepath = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getOpenFileName(this, tr("选择目标文件"), filepath, tr("launch文件(*launch)"), 0,QFileDialog::DontUseNativeDialog);
    ui->LaunchPathLine->setText(filename);
    QString SectionName = "launch/";
    MySetting->setValue(SectionName + "launch", filename);
    getParamList();
}

void MainWindow::saveChange()
{
    QFile launchFile(ui->LaunchPathLine->text().toLatin1().data());
    launchFile.open(QIODevice::Text | QIODevice::ReadWrite);
    QString text, allString;
//    QTextStream ts(&launchFile);
    while (!launchFile.atEnd()) {
        text=launchFile.readLine();
        int index = text.indexOf("param");
        if(index!=-1) { // 存在目标字符串
            for (int i=0;i<text.length();++i) {
                if (text[i] == '='){ // 在QListwidget中添加元素
                    // 寻找name和参数值的起止地址
                    int nameStart=0, nameEnd=i;
                    int paramStart=i+2, paramEnd=0;
                    for(int j=nameEnd;j>0;--j)
                        if(text[j]==' '){
                            nameStart=j+1;
                            break;
                        }

                    for(int j=paramStart;j<text.size();++j)
                        if(text[j]=='\"'){
                            paramEnd=j;
                            break;
                        }

                    QString paramname = text.mid(nameStart, nameEnd-nameStart);
                    QString paramvalue = text.mid(paramStart, paramEnd-paramStart);
                    QString newvalue;

                    for (int i=0;i<ui->paramList->count() ;++i ) {
                        QListWidgetItem* WContainerItem=ui->paramList->item(i);
                        QWidget* pwig = ui->paramList->itemWidget(WContainerItem);
                        QLabel * label = pwig->findChild<QLabel *>(paramname);
                        QLineEdit * lineedit = pwig->findChild<QLineEdit *>(paramvalue);
                        if(label){
                            qDebug() << " 成功找到 " << paramname <<Qt::endl;
                            text.replace(paramvalue, lineedit->text().toLatin1());
                        }

                    }
                }
            }
            allString+=text;
        }
        else{
            allString+=text;
        }
    }
    launchFile.close();
    launchFile.remove();
    QFile launchFile2(ui->LaunchPathLine->text().toLatin1().data());
    launchFile2.open(QIODevice::Text | QIODevice::ReadWrite);
    launchFile2.write(allString.toUtf8(), allString.size());
    launchFile2.close();
}

void MainWindow::referencePath()
{
    QString filepath = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getOpenFileName(this, tr("选择目标文件"), filepath, tr("csv文件(*csv)"), 0,QFileDialog::DontUseNativeDialog);
    ui->ReferencePathLine->setText(filename);
    QString SectionName = "plot/";
    MySetting->setValue(SectionName + "referenceFile", filename);
}

void MainWindow::currentPathDic()
{
    QString filepath = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getExistingDirectory(this, tr("选择目标文件"), filepath);
    ui->CurrentPathDicLine->setText(filename);
    QString SectionName = "plot/";
    MySetting->setValue(SectionName + "dataDic", filename);
}

void MainWindow::plotPath()
{
//    system("python3 "+ ui->PythonFilePathLine->text().toLatin1() + " " + ui->ReferencePathLine->text().toLatin1() + " " +
//           ui->CurrentPathDicLine->text().toLatin1() + " " + QString::number(ui->PathCountBox->value()).toLatin1());
    char line[1000];
    fpin=popen("python3 "+ ui->PythonFilePathLine->text().toLatin1() + " " + ui->ReferencePathLine->text().toLatin1() + " " +
                                ui->CurrentPathDicLine->text().toLatin1() + " " + QString::number(ui->PathCountBox->value()).toLatin1(), "r");
    if(fpin==NULL)
        qDebug() << "popen error" << Qt::endl;
    else{
        while(fgets(line, sizeof (line), fpin)!=NULL)
            ui->LogOutputText->append(line);
    }
    fpin=NULL;
}

void MainWindow::roslaunchFile()
{

//    BashThread->setBash("python3 "+ ui->PythonFilePathLine->text().toLatin1() + " " + ui->ReferencePathLine->text().toLatin1() + " " +
//                        ui->CurrentPathDicLine->text().toLatin1() + " " + QString::number(ui->PathCountBox->value()).toLatin1());
    BashThread->setBash("bash " + ui->ShellPathLine->text());
    WorkThread->start();
    dummy.emitsig();
    BashTimer->start(10);
    qDebug() << "main thread: " << QThread::currentThreadId();
    connect(BashTimer, SIGNAL(timeout()), this, SLOT(RefreshBashMessage()));

    qDebug() << "roslaunchFile" << Qt::endl;
}

void MainWindow::pythonFilePath()
{
    QString filepath = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getOpenFileName(this, tr("选择目标文件"), filepath, tr("python文件(*py)"), 0,QFileDialog::DontUseNativeDialog);
    ui->PythonFilePathLine->setText(filename);
    QString SectionName = "plot/";
    MySetting->setValue(SectionName + "pythonFile", filename);
}

void MainWindow::roslaunchStopFile()
{
    fpin=BashThread->getFilePope();
    if(fpin==NULL){
        ui->LogOutputText->append("未开始Ros程序，无需关闭");
        return;
    }
    ui->LogOutputText->append("------------------------------------------------------");
    BashThread->MyThreadClose();
    WorkThread->destroyed();
    disconnect(BashTimer, SIGNAL(timeout()), this, SLOT(RefreshBashMessage()));
    BashTimer->stop();

    ui->LogOutputText->append("---------------------------Info-----------------------");
    ui->LogOutputText->append("The Roslaunch has been closed!");
    ui->LogOutputText->append("------------------------------------------------------");
}

void MainWindow::RefreshBashMessage()
{
    char line[1000];
    fpin=BashThread->getFilePope();
    if(fpin==NULL){
        qDebug() << "popen error" << Qt::endl;
        ui->LogOutputText->append("popen error");
    }
    else if(fgets(line, sizeof (line), fpin)!=NULL){
        if(ui->LogOutputText->document()->lineCount()>200)
            ui->LogOutputText->clear();
        ui->LogOutputText->append(line);
    }
}

void MainWindow::shellSelect()
{
    QString filepath = QCoreApplication::applicationDirPath();
    QString filename = QFileDialog::getOpenFileName(this, tr("选择目标文件"), filepath, tr("shell文件(*sh)"), 0,QFileDialog::DontUseNativeDialog);
    ui->ShellPathLine->setText(filename);
    QString SectionName = "launch/";
    MySetting->setValue(SectionName + "shell", filename);
}
