#include "mc3512scanner.h"

#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3512Scanner::MC3512Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3512Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<quint16> bitData;
    QVector<bool> res = ModbusProtocol::readDiscreteInputs(*sPort,addr,0,8,waitTime);
    if(res.count()>=8) {
        ++corrAnswCnt;
        quint16 bitState=0;
        for(int i=0;i<8;i++) if(res.at(i)) bitState |= 1<<i;
        bitData.append(bitState);
        res = ModbusProtocol::readCoils(*sPort,addr,0,8,waitTime);
        if(res.count()>=8) {
            bitState=0;
            for(int i=0;i<8;i++) if(res.at(i)) bitState |= 1<<i;
            bitData.append(bitState);
            emit ioData(bitData);
            emit correctAnswer(++corrAnswCnt);
        }else emit answerError();
    }else emit answerError();
}

void MC3512Scanner::writeCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(ModbusProtocol::writeSingleCoil(*sPort,addr,writeNum,writeValue,waitTime)) emit correctAnswer(++corrAnswCnt);
    else emit answerError();
}
