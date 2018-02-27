#include "abstractscanner.h"
#include <QMutexLocker>
#include <QThread>
#include "modbusprotocol.h"

AbstractScanner::AbstractScanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :
    QObject(parent), startFlag(false), stopFlag(false), readConfFlag(false),writeConfFlag(false),
    writeDataFlag(false),finishFlag(false), port(pName), addr(netAddr), baud(baudrate),
    stopBits(stopBits),parity(parity),sPort(nullptr),
    corrAnswCnt(0),writeNum(0), writeValue(0)
{
    qRegisterMetaType<QVector<quint16> >("QVector<quint16>");
    switch(baud) {
        case 115200:waitTime=100;break;
        case 57600:waitTime=100;break;
        case 38400:waitTime=100;break;
        case 19200:waitTime=100;break;
        case 9600:waitTime=200;break;
        default:waitTime=200;break;
    }

}

void AbstractScanner::startScan()
{
    QMutexLocker locker(&mutex);
    startFlag = true;
}

void AbstractScanner::stopScan()
{
    QMutexLocker locker(&mutex);
    stopFlag = true;
}

void AbstractScanner::readConf()
{
    QMutexLocker locker(&mutex);
    readConfFlag = true;
}

void AbstractScanner::writeConf(QVector<quint16> conf)
{
    QMutexLocker locker(&mutex);
    writeConfFlag = true;
    writeDt = conf;
}

void AbstractScanner::finishProcess()
{
    QMutexLocker locker(&mutex);
    finishFlag = true;
}

void AbstractScanner::writeData(int num, quint16 value)
{
    QMutexLocker locker(&mutex);
    writeDataFlag = true;
    writeNum = num;
    writeValue = value;
}

void AbstractScanner::scanCycle()
{
    sPort = new QSerialPort(port);
    sPort->setDataBits(QSerialPort::Data8);
    if(stopBits==1) sPort->setStopBits(QSerialPort::OneStop);
    else sPort->setStopBits(QSerialPort::TwoStop);
    switch(parity) {
        case 0: sPort->setParity(QSerialPort::NoParity);break;
        case 1: sPort->setParity(QSerialPort::OddParity);break;
        case 2: sPort->setParity(QSerialPort::EvenParity);break;
        default:sPort->setParity(QSerialPort::NoParity);
    }

    sPort->setBaudRate(baud);
    forever{
        if(!sPort->isOpen()) sPort->open(QSerialPort::ReadWrite);
        if(sPort->isOpen()) {
            mutex.lock();
            if(readConfFlag) {readConfFlag = false; mutex.unlock(); readConfiguration();}else mutex.unlock();
            mutex.lock();
            if(writeConfFlag) {writeConfFlag = false; mutex.unlock(); writeConfiguration();}else mutex.unlock();
            mutex.lock();
            if(writeDataFlag) { writeDataFlag = false; if(startFlag) {mutex.unlock();writeCycle();} else mutex.unlock(); }else mutex.unlock();
            mutex.lock();
            if(startFlag) { mutex.unlock(); readCycle();}else mutex.unlock();
            mutex.lock();
            if(stopFlag) { stopFlag = false; startFlag = false; mutex.unlock();}else mutex.unlock();
        }else emit answerError();
        QThread::msleep(1);
        mutex.lock();
        if(finishFlag) {mutex.unlock();break;}else mutex.unlock();
    }
    sPort->close();
}

void AbstractScanner::readConfiguration()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<quint16> res = ModbusProtocol::readHoldRegs(*sPort,addr,confStartAddress,confLength,waitTime);
    if(res.count()>=confLength) {
        QVector<quint16> cData;
        set_conf_data(cData,res);
        QVector<quint8> res = ModbusProtocol::getSlaveID(*sPort,addr,waitTime);
        if(res.count()>=6) {
            int vers = (((quint16)((quint8)res.at(4))) << 8) | res.at(5);
            cData.append(vers);
            emit confData(cData);
            emit correctAnswer(++corrAnswCnt);
            emit info("Настройки успешно прочитаны");
        }else {emit answerError();emit info("Ошибка чтения настроек");}
    }else {emit answerError();emit info("Ошибка чтения настроек");}
}

void AbstractScanner::writeConfiguration()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(ModbusProtocol::writeMultiRegs(*sPort,addr,confStartAddress,writeDt,waitTime)) {
        emit correctAnswer(++corrAnswCnt);
        emit info("Настройки успешно записаны");
    }else {emit answerError();emit info("Ошибка записи настроек");}
}
