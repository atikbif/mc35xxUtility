#include "mc3520scanner.h"
#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3520Scanner::MC3520Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :
    AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3520Scanner::readCycle()
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
        QVector<bool> doRes = ModbusProtocol::readCoils(*sPort,addr,0,2,waitTime);
        if(doRes.count()>=2) {
            foreach (bool bitValue, doRes) {
                if(bitValue) bitData.append(1);else bitData.append(0);
            }
            emit ioData(bitData);
            emit correctAnswer(++corrAnswCnt);
        }else emit answerError();
    }else emit answerError();
}

void MC3520Scanner::writeCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(ModbusProtocol::writeSingleCoil(*sPort,addr,writeNum,writeValue,waitTime)) emit correctAnswer(++corrAnswCnt);
    else emit answerError();
}
