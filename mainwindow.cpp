#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mcfinder.h"
#include <QSerialPortInfo>
#include <QTimer>
#include <QTextBrowser>
#include "QTabWidget"

#include "mc3510gui.h"
#include "mc3510scanner.h"
#include "mc3511gui.h"
#include "mc3511scanner.h"
#include "mc3512gui.h"
#include "mc3512scanner.h"
#include "mc3513gui.h"
#include "mc3513scanner.h"
#include "mc3514gui.h"
#include "mc3514scanner.h"
#include "mc3516gui.h"
#include "mc3516scanner.h"
#include "mc3517gui.h"
#include "mc3517scanner.h"
#include "mc3518gui.h"
#include "mc3518scanner.h"
#include "mc3520gui.h"
#include "mc3520scanner.h"
#include "mc3521gui.h"
#include "mc3521scanner.h"
#include "mc3523gui.h"
#include "mc3523scanner.h"
#include "mc3525gui.h"
#include "mc3525scanner.h"
#include "mc3556gui.h"
#include "mc3556scanner.h"

using LinkPtr = QSharedPointer<LinkManager>;
using GUIPtr = QSharedPointer<AbstractGUI>;

std::map<QString,std::function<std::pair<LinkPtr,GUIPtr>(QString,int,qint32,int,int)>> MainWindow::mod_map {
    {"MC3510",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3510Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3510GUI>(new MC3510GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3511",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3511Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3511GUI>(new MC3511GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3512",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3512Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3512GUI>(new MC3512GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3513",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3513Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3513GUI>(new MC3513GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3514",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3514Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3514GUI>(new MC3514GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3516",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3516Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3516GUI>(new MC3516GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3517",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3517Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3517GUI>(new MC3517GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3518",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3518Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3518GUI>(new MC3518GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3520",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3520Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3520GUI>(new MC3520GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3521",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3521Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3521GUI>(new MC3521GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3523",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3523Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3523GUI>(new MC3523GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3525",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3525Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3525GUI>(new MC3525GUI());
        return std::make_pair(link,gui);
    }},
    {"MC3556",[](const QString pName, int netAddr, qint32 baudrate, int stopBits, int parity){
        LinkPtr link = QSharedPointer<LinkManager>::create(new MC3556Scanner(pName,netAddr,baudrate,stopBits,parity));
        GUIPtr gui = QSharedPointer<MC3556GUI>(new MC3556GUI());
        return std::make_pair(link,gui);
    }}
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    foreach(QSerialPortInfo pInfo,QSerialPortInfo::availablePorts()) {
        ui->comboBox->addItem(pInfo.portName());
    }
    ui->comboBox->addItem("AUTO");
    ui->comboBox->setCurrentText("AUTO");

    widgetLayout = new QVBoxLayout();
    ui->groupBox_Mod->setLayout(widgetLayout);
    showInfoWidget();

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updatePortList);
    timer->start(3000);
    setWindowFlags(Qt::Dialog);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->pushButtonStartStop->text()=="Стоп") on_pushButtonStartStop_clicked();
    showInfoWidget();
    mLink.clear();
    mGUI.clear();
    ui->lineEditName->setText("");

    stopBits = 1;
    parity = 0;
    MCFinder *finder = new MCFinder(ui->spinBox->value(), ui->comboBox->currentText());
    connect(finder,&MCFinder::updateBaud,this, [this](unsigned long value){baud=value;});
    connect(finder,&MCFinder::updateStopBits,this, [this](int value){stopBits=value;});
    connect(finder,&MCFinder::updateParity,this, [this](int value){parity=value;});
    connect(finder,&MCFinder::updateNetAddr,this,[this](int value){ui->spinBox->setValue(value);});
    connect(finder,&MCFinder::updatePortName,this,[this](QString pName){ui->comboBox->setCurrentText(pName);});
    connect(finder,&MCFinder::updateName,this,[this](QString modName){ui->lineEditName->setText(modName);});
    connect(finder,&MCFinder::foundModule,this,&MainWindow::found);
}

void MainWindow::updatePortList()
{
    QStringList pList;
    QString currentPort = ui->comboBox->currentText();
    foreach(QSerialPortInfo pInfo,QSerialPortInfo::availablePorts()) {
        pList.append(pInfo.portName());
    }
    pList.append("AUTO");
    qSort(pList);
    QStringList currentList;
    for(int i=0;i<ui->comboBox->count();i++) {
        currentList.append(ui->comboBox->itemText(i));
    }
    qSort(currentList);
    bool compareFlag = true;
    if(currentList.count()!=pList.count()) compareFlag = false;
    else {
        for(int i=0;i<pList.count();i++) {
            if(pList.at(i)!=currentList.at(i)) compareFlag = false;
        }
    }
    if(compareFlag==false) {
        ui->comboBox->clear();
        foreach(QString pName, pList) {
            ui->comboBox->addItem(pName);
        }
        if(pList.contains(currentPort)) ui->comboBox->setCurrentText(currentPort);
        else ui->comboBox->setCurrentText("AUTO");
        ui->comboBox->repaint();
    }
}

void MainWindow::found()
{
    clearInfoWidget();

    QString mName = ui->lineEditName->text();
    //mName = "MC3556";
    if(!mName.isEmpty()) {
        auto it = mod_map.find(mName);
        if(it!=mod_map.end()) {
            auto res = it->second(ui->comboBox->currentText(),ui->spinBox->value(), baud,stopBits,parity);
            mLink = res.first;
            mGUI = res.second;

            QWidget *ptr = mGUI->createWidget();

            connect(mLink.data(),&LinkManager::confData,mGUI.data(),&AbstractGUI::confData);
            connect(mLink.data(),&LinkManager::ioData,mGUI.data(), &AbstractGUI::ioData);
            connect(mGUI.data(),&AbstractGUI::readConf,mLink.data(),&LinkManager::readConf);
            connect(this,&MainWindow::startScan,mLink.data(),&LinkManager::startScan);
            connect(this,&MainWindow::stopScan,mLink.data(),&LinkManager::stopScan);
            connect(mGUI.data(),&AbstractGUI::writeConf,mLink.data(),&LinkManager::writeConf);
            connect(mLink.data(),&LinkManager::correctAnswer,this,&MainWindow::correctAnswer);
            connect(mLink.data(),&LinkManager::answerError,this,&MainWindow::answerError);
            connect(mGUI.data(),&AbstractGUI::writeData,mLink.data(),&LinkManager::writeData);
            connect(mLink.data(),&LinkManager::info,this,&MainWindow::info);
            mLink->readConf();
            widgetLayout->addWidget(ptr);

            ui->pushButtonStartStop->setVisible(true);
            ui->lcdNumberAnswerCounter->setVisible(true);
            ui->lcdNumberAnswerCounter->setStyleSheet("background-color: light-gray;");
            ui->lcdNumberAnswerCounter->setPalette(Qt::darkYellow);
        }
    }
}

void MainWindow::info(QString value)
{
    ui->statusBar->showMessage(value,2000);
}

void MainWindow::answerError()
{
    static bool blinkFlag = false;

    ui->lcdNumberAnswerCounter->setStyleSheet("background-color: darkRed;");
    if(blinkFlag) {
        ui->lcdNumberAnswerCounter->setPalette(Qt::white);
        blinkFlag = false;
    }
    else {
        ui->lcdNumberAnswerCounter->setPalette(Qt::black);
        blinkFlag = true;
    }
}

void MainWindow::correctAnswer(int cnt)
{
    ui->lcdNumberAnswerCounter->display(cnt);
    ui->lcdNumberAnswerCounter->setStyleSheet("background-color: darkGray;");
    ui->lcdNumberAnswerCounter->setPalette(Qt::white);
}

void MainWindow::showInfoWidget()
{
    clearInfoWidget();
    QTextBrowser *info = new QTextBrowser();
    info->append("<i>Выберите COM порт и сетевой адрес, нажмите кнопку \"Поиск\" для подключения к модулю ввода/вывода</i>");
    widgetLayout->addWidget(info);
}

void MainWindow::clearInfoWidget()
{
    QLayoutItem* item;
    while((item = widgetLayout->takeAt(0)) != nullptr )
    {
        delete item->widget();
        delete item;
    }
    ui->pushButtonStartStop->setVisible(false);
    ui->lcdNumberAnswerCounter->setVisible(false);
}

void MainWindow::on_pushButtonStartStop_clicked()
{
    if(ui->pushButtonStartStop->text()=="Старт") {
        ui->pushButtonStartStop->setText("Стоп");
        emit startScan();
    }else {
        ui->pushButtonStartStop->setText("Старт");
        ui->lcdNumberAnswerCounter->setPalette(Qt::white);
        emit stopScan();
    }
}
