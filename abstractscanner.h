#ifndef ABSTRACTSCANNER_H
#define ABSTRACTSCANNER_H

#include <QObject>
#include <QMutex>
#include <QSerialPort>
#include <Qvector>

class AbstractScanner : public QObject
{
    Q_OBJECT

protected:
    QMutex mutex;
    bool startFlag;
    bool stopFlag;
    bool readConfFlag;
    bool writeConfFlag;
    bool writeDataFlag;
    bool finishFlag;
    QString port;
    int addr;
    qint32 baud;
    int stopBits;
    int parity;
    QSerialPort *sPort;
    int corrAnswCnt;
    QVector<quint16> writeDt;
    int writeNum;
    quint16 writeValue;
    quint16 waitTime;

    static const quint16 confStartAddress = 64;

public:
    static const quint16 confLength = 7;
    enum ConfAddr {NET_ADDR,DI_FILTER,AI_FILTER,BAUD,TIME_OUT_OFF,STOP_BITS,PARITY};
    static QVector<quint16> getEmptyConf() {return QVector<quint16>(confLength);}
    explicit AbstractScanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
    void startScan();
    void stopScan();
    void readConf();
    void writeConf(QVector<quint16> conf);
    void finishProcess();
    void writeData(int num, quint16 value);

signals:
    confData(QVector<quint16> conf);
    ioData(QVector<quint16> io);
    answerError();
    correctAnswer(int answerCounter);
    info(QString value);
public slots:
    void scanCycle();
protected:
    void readConfiguration();
    void writeConfiguration();
    virtual void readCycle() {}
    virtual void writeCycle() {}
    virtual void set_conf_data(QVector<quint16> &conf_data, const QVector<quint16> &modbus_hold_regs) {
        for(auto value:modbus_hold_regs) {conf_data.append(value);}
    }    
};

#endif // ABSTRACTSCANNER_H
