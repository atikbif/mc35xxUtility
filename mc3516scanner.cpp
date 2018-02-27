#include "mc3516scanner.h"

#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3516Scanner::MC3516Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3516Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<quint16> res = ModbusProtocol::readInpRegs(*sPort,addr,0,8,waitTime);
    if(res.count()>=8) {
        emit ioData(res);
        emit correctAnswer(++corrAnswCnt);
    }else emit answerError();
}

void MC3516Scanner::writeCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(ModbusProtocol::writeMultiRegs(*sPort,addr,writeNum,QVector<quint16>{writeValue},waitTime)) emit correctAnswer(++corrAnswCnt);
    else emit answerError();
}
