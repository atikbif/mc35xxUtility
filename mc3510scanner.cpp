#include "mc3510scanner.h"
#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3510Scanner::MC3510Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :
    AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3510Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<bool> res = ModbusProtocol::readDiscreteInputs(*sPort,addr,0,16,waitTime);
    if(res.count()>=16) {
        quint16 bitState=0;
        for(int i=0;i<16;i++) if(res.at(i)) bitState |= 1<<i;
        emit ioData(QVector<quint16>{bitState});
        emit correctAnswer(++corrAnswCnt);
    }else emit answerError();
}
