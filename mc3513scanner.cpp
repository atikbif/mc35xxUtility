#include "mc3513scanner.h"

#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3513Scanner::MC3513Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3513Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<quint16> resData;
    QVector<bool> res = ModbusProtocol::readDiscreteInputs(*sPort,addr,0,8,waitTime);
    if(res.count()>=8) {
        ++corrAnswCnt;
        quint16 bitState=0;
        for(int i=0;i<8;i++) if(res.at(i)) bitState |= 1<<i;
        resData.append(bitState);
        QVector<quint16> adcRes = ModbusProtocol::readInpRegs(*sPort,addr,0,8,waitTime);
        if(adcRes.count()>=8) {
            resData.append(adcRes);
            emit ioData(resData);
            emit correctAnswer(++corrAnswCnt);
        }else emit answerError();
    }else emit answerError();
}

