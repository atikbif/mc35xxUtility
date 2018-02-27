#ifndef MODBUSPROTOCOL_H
#define MODBUSPROTOCOL_H

#include <QSerialPort>
#include <QVector>


class ModbusProtocol
{
    static const unsigned char crc16H[256];
    static const unsigned char crc16L[256];

    static void addCRC(QByteArray &buf);
public:
    ModbusProtocol();
    static QVector<bool> readCoils(QSerialPort &port, int &netAddr, int memAddr, int cnt, int waitTime);
    static QVector<bool> readDiscreteInputs(QSerialPort &port, int &netAddr, int memAddr, int cnt, int waitTime);
    static QVector<quint16> readHoldRegs(QSerialPort &port, int &netAddr, int memAddr, int cnt, int waitTime);
    static QVector<quint16> readInpRegs(QSerialPort &port, int &netAddr, int memAddr, int cnt, int waitTime);
    static bool writeSingleCoil(QSerialPort &port, int &netAddr, int memAddr, bool value, int waitTime);
    static bool writeSingleReg(QSerialPort &port, int &netAddr, int memAddr, quint16 value, int waitTime);
    static bool writeMultiRegs(QSerialPort &port, int &netAddr, int memAddr, const QVector<quint16> &rData, int waitTime);
    static QVector<quint16> readWriteMultiRegs(QSerialPort &port, int &netAddr, int readMemAddr, int wrMemAddr,
                                               int readCnt, const QVector<quint16> &rData, int waitTime);
    static QVector<quint8> getSlaveID(QSerialPort &port, int &netAddr, int waitTime);
};

#endif // MODBUSPROTOCOL_H
