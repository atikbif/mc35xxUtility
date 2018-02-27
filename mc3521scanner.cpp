#include "mc3521scanner.h"
#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3521Scanner::MC3521Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :
    AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3521Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<quint16> bitData;
    QVector<bool> res = ModbusProtocol::readCoils(*sPort,addr,0,10,waitTime);
    if(res.count()>=10) {
        ++corrAnswCnt;
        quint16 bitState=0;
        for(int i=0;i<10;i++) if(res.at(i)) bitState |= 1<<i;
        bitData.append(bitState);
        emit ioData(bitData);
        emit correctAnswer(++corrAnswCnt);
    }else emit answerError();
}

void MC3521Scanner::writeCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(ModbusProtocol::writeSingleCoil(*sPort,addr,writeNum,writeValue,waitTime)) emit correctAnswer(++corrAnswCnt);
    else emit answerError();
}
