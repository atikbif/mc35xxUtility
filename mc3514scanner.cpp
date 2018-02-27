#include "mc3514scanner.h"

#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3514Scanner::MC3514Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3514Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<quint16> res = ModbusProtocol::readInpRegs(*sPort,addr,0,8,waitTime);
    if(res.count()>=8) {
        ++corrAnswCnt;
        QVector<bool> bitRes = ModbusProtocol::readCoils(*sPort,addr,0,8,waitTime);
        if(bitRes.count()>=8) {
            quint16 bitState=0;
            for(int i=0;i<8;i++) if(bitRes.at(i)) bitState |= 1<<i;
            res.append(bitState);
            emit ioData(res);
            emit correctAnswer(++corrAnswCnt);
        }else emit answerError();
    }else emit answerError();
}

void MC3514Scanner::writeCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(ModbusProtocol::writeSingleCoil(*sPort,addr,writeNum,writeValue,waitTime)) emit correctAnswer(++corrAnswCnt);
    else emit answerError();
}
