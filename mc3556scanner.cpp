#include "mc3556scanner.h"

#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3556Scanner::MC3556Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3556Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<quint16> adcRes = ModbusProtocol::readInpRegs(*sPort,addr,0,16,waitTime);
    if(adcRes.count()>=16) {
        emit ioData(adcRes);
        emit correctAnswer(++corrAnswCnt);
    }else emit answerError();
}
