#include "mc3523scanner.h"
#include <QMutexLocker>
#include <QThread>
#include <QSerialPort>
#include "modbusprotocol.h"

MC3523Scanner::MC3523Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent) :
    AbstractScanner(pName,netAddr,baudrate,stopBits,parity,parent)
{

}

void MC3523Scanner::readCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    QVector<quint16> res = ModbusProtocol::readInpRegs(*sPort,addr,0,8,waitTime);
    if(res.count()>=8) {
        QVector<bool> doRes = ModbusProtocol::readCoils(*sPort,addr,0,2,waitTime);
        if(doRes.count()>=2) {
            foreach (bool bitValue, doRes) {
                if(bitValue) res.append(1);else res.append(0);
            }
            emit ioData(res);
            emit correctAnswer(++corrAnswCnt);
        }else emit answerError();
    }else emit answerError();
}

void MC3523Scanner::writeCycle()
{
    if(sPort==nullptr) return;
    if(!sPort->isOpen()) return;
    if(ModbusProtocol::writeSingleCoil(*sPort,addr,writeNum,writeValue,waitTime)) emit correctAnswer(++corrAnswCnt);
    else emit answerError();
}
