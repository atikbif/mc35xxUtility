#include "mc3518scanner.h"

#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3518Scanner::MC3518Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3518Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<bool> res = ModbusProtocol::readCoils(*sPort,addr,0,8,waitTime);
    if(res.count()>=8) {
        quint16 bitState=0;
        for(int i=0;i<8;i++) if(res.at(i)) bitState |= 1<<i;
        emit ioData(QVector<quint16>{bitState});
        emit correctAnswer(++corrAnswCnt);
    }else emit answerError();
}

void MC3518Scanner::writeCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(writeNum<2) {
        if(ModbusProtocol::writeMultiRegs(*sPort,addr,writeNum,QVector<quint16>{writeValue},waitTime)) emit correctAnswer(++corrAnswCnt);
        else emit answerError();
    }else {
        if(ModbusProtocol::writeSingleCoil(*sPort,addr,writeNum-2,writeValue,100)) emit correctAnswer(++corrAnswCnt);
        else emit answerError();
    }
}
