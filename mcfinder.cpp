#include "mcfinder.h"
#include <QStringList>
#include <QSerialPortInfo>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>


MCFinder::MCFinder(int netAddr, const QString &portName, QObject *parent) : QObject(parent), dialog(nullptr),
    foundFlag(false)
{
    QStringList pNames;
    if(portName.contains("COM")) {
        pNames.append(portName);
    }else {
        foreach(QSerialPortInfo pInfo,QSerialPortInfo::availablePorts()) {
            pNames.append(pInfo.portName());
        }
    }
    if(pNames.count()) {
        emit stopScan();
        QThread::msleep(200);
        dialog = new QDialog();
        dialog->setWindowTitle("Поиск модулей");
        connect(dialog,&QDialog::finished,this,&MCFinder::deleteLater);
        QVBoxLayout *layout = new QVBoxLayout(dialog);

        foreach(QString pName, pNames) {
            FinderThread *worker = new FinderThread(pName,netAddr);
            finders.append(worker);
            QThread *thread = new QThread();
            threads.append(thread);
            worker->moveToThread(thread);

            connect(thread,&QThread::finished,worker,&FinderThread::deleteLater);
            connect(this,&MCFinder::startSearch,worker,&FinderThread::startSearch);
            connect(worker,&FinderThread::percentUpdate,this,&MCFinder::percentUpdate);
            connect(worker,&FinderThread::found,this,&MCFinder::found);
            thread->start();
            QProgressBar *bar = new QProgressBar();
            QHBoxLayout *hLayout = new QHBoxLayout();
            hLayout->addWidget(new QLabel(pName+":"));
            hLayout->addWidget(bar);
            layout->addLayout(hLayout);
            bars.insert(pName,bar);
        }
        emit startSearch();
        dialog->show();
    }

}

MCFinder::~MCFinder()
{
    foreach (FinderThread* worker, finders) {
       worker->stopSearch();
    }
    foreach (QThread* thread, threads) {
        thread->quit();
        thread->wait();
    }
    if(dialog) delete dialog;
}

void MCFinder::percentUpdate(QString pName, double value)
{
    if(bars.keys().contains(pName)) {
        QProgressBar *bar = bars.value(pName);
        bar->setValue(value+0.5);
    }
    bool prContinue = false;
    foreach(QProgressBar *bar,bars.values()) {
        if(bar->value()!=bar->maximum()) prContinue = true;
    }
    if(prContinue==false) {
        QTimer::singleShot(100,this,SLOT(checkFoundFlag()));
    }
}

void MCFinder::found(QString pName, int baudRate, int stopBits, int parity, int netAddr, QString modName)
{
    foundFlag = true;
    if(dialog!=nullptr) {
        QLabel *message = new QLabel("Обнаружен модуль " + modName +
                                     " порт: " + pName);
        emit updateNetAddr(netAddr);
        emit updatePortName(pName);
        emit updateBaud(baudRate);
        emit updateStopBits(stopBits);
        emit updateParity(parity);
        emit updateName(modName);
        dialog->layout()->addWidget(message);
        dialog->repaint();
        emit foundModule();
        QTimer::singleShot(500,this,SLOT(deleteLater()));
    }
}

void MCFinder::checkFoundFlag()
{
    if((!foundFlag)&&(dialog!=nullptr)) {
        QLabel *message = new QLabel("Модули не обнаружены!");
        dialog->layout()->addWidget(message);
        QTimer::singleShot(2000,this,SLOT(deleteLater()));
    }
}
