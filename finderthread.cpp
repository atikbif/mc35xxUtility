#include "finderthread.h"
#include <QSerialPort>
#include <QThread>
#include "modbusprotocol.h"

QVector<qint32> FinderThread::baudTable = {QSerialPort::Baud115200,QSerialPort::Baud57600,QSerialPort::Baud38400,
            QSerialPort::Baud19200,QSerialPort::Baud9600};

QString FinderThread::getModNameByID(const QVector<quint8> id)
{
    QString res;
    if(id.count()>=4) {
        if((id.at(2)==14)&&(id.at(3)==10)) {    // code for modules
            switch(id.at(0)) {
                case 0:res = "MC3510";break;
                case 1:res = "MC3511";break;
                case 2:res = "MC3512";break;
                case 3:res = "MC3513";break;
                case 4:res = "MC3514";break;
                case 5:res = "MC3515";break;
                case 6:res = "MC3516";break;
                case 7:res = "MC3517";break;
                case 8:res = "MC3518";break;
                case 9:res = "MC3519";break;
                case 10:res = "MC3520";break;
                case 11:res = "MC3521";break;
                case 12:res = "MC3522";break;
                case 13:res = "MC3523";break;
                case 14:res = "MC3530";break;
            }
        }
    }
    return res;
}

bool FinderThread::startSearchWithPortConf(quint8 stopBits, quint8 parity, double startPercent, double percentDelta)
{
    bool funcRes = false;
    QSerialPort port(portName);
    port.setDataBits(QSerialPort::Data8);
    if(stopBits==1) port.setStopBits(QSerialPort::OneStop);
    else port.setStopBits(QSerialPort::TwoStop);
    switch(parity) {
        case 0:port.setParity(QSerialPort::NoParity);break;
        case 1:port.setParity(QSerialPort::OddParity);break;
        case 2:port.setParity(QSerialPort::EvenParity);break;
        default:port.setParity(QSerialPort::NoParity);
    }

    port.setBaudRate(QSerialPort::Baud115200);
    if(port.open(QSerialPort::ReadWrite)) {
        quint16 waitDelay = 100;

        double percValue = startPercent;
        QString modName;
        int netAddr;
        foreach (qint32 baud, baudTable) {
            switch(baud) {
                case 115200:waitDelay=100;break;
                case 57600:waitDelay=100;break;
                case 38400:waitDelay=100;break;
                case 19200:waitDelay=100;break;
                case 9600:waitDelay=200;break;
                default:waitDelay=200;break;
            }

            mutex.lock();
            if(stopFlag) {mutex.unlock();break;}
            mutex.unlock();
            port.setBaudRate(baud);
            percValue+=percentDelta;
            emit percentUpdate(portName,percValue);
            netAddr = netAddress;
            QVector<quint8> res = ModbusProtocol::getSlaveID(port,netAddr,waitDelay);
            if(res.count()) {
                modName = getModNameByID(res);
                if(!modName.isEmpty()) {
                    emit found(portName,baud,stopBits,parity,netAddr,modName);
                    funcRes = true;
                    break;
                }
            }
            QThread::msleep(1);
        }
        port.close();
        if(modName.isEmpty()) emit failed(portName);
    }else {
        emit failed(portName);
        emit percentUpdate(portName,100);
    }
    return funcRes;
}

FinderThread::FinderThread(const QString &pName, int netAddr, QObject *parent) : QObject(parent),
    portName(pName), stopFlag(false), netAddress(netAddr)
{

}

void FinderThread::startSearch()
{
    int confVariantCnt = 6; // число вариантов конфигурации порта
    double offset = 100.0 / confVariantCnt;
    double delta = offset / baudTable.length();
    double startPercent = 0;
    bool res = startSearchWithPortConf(1,0,startPercent,delta);startPercent+=offset;
    if(!res) {res = startSearchWithPortConf(1,1,startPercent,delta);startPercent+=offset;}
    if(!res) {res = startSearchWithPortConf(1,2,startPercent,delta);startPercent+=offset;}
    if(!res) {res = startSearchWithPortConf(2,0,startPercent,delta);startPercent+=offset;}
    if(!res) {res = startSearchWithPortConf(2,1,startPercent,delta);startPercent+=offset;}
    if(!res) {res = startSearchWithPortConf(2,2,startPercent,delta);startPercent+=offset;}
    if(!res) {
        emit failed(portName);
    }
}

void FinderThread::stopSearch()
{
    QMutexLocker locker(&mutex);
    stopFlag = true;
}
