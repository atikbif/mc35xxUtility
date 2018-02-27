#include "mc3511scanner.h"

#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3511Scanner::MC3511Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity,QObject *parent) :AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3511Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<bool> res = ModbusProtocol::readCoils(*sPort,addr,0,16,waitTime);
    if(res.count()>=16) {
        quint16 bitState=0;
        for(int i=0;i<16;i++) if(res.at(i)) bitState |= 1<<i;
        emit ioData(QVector<quint16>{bitState});
        emit correctAnswer(++corrAnswCnt);
    }else emit answerError();
}

void MC3511Scanner::writeCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(ModbusProtocol::writeSingleCoil(*sPort,addr,writeNum,writeValue,waitTime)) emit correctAnswer(++corrAnswCnt);
    else emit answerError();
}
