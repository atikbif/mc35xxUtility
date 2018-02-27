#ifndef MCFINDER_H
#define MCFINDER_H

#include <QObject>
#include <QString>
#include "finderthread.h"
#include <QThread>
#include <QVector>
#include <QHash>
#include <QProgressBar>

class MCFinder : public QObject
{
    Q_OBJECT
    QVector<FinderThread*> finders;
    QVector<QThread*> threads;
    QHash<QString,QProgressBar*> bars;
    QDialog *dialog;
    bool foundFlag;
public:
    explicit MCFinder(int netAddr = 0, const QString &portName="", QObject *parent = 0);
    ~MCFinder();
signals:
    stopScan();
    updateStopBits(int value);
    updateParity(int value);
    updateNetAddr(int value);
    updatePortName(QString pName);
    updateBaud(unsigned long value);
    updateName(QString modName);
    startSearch();
    foundModule();
private slots:
    void percentUpdate(QString pName, double value);
    void found(QString pName, int baudRate, int stopBits, int parity, int netAddr, QString modName);
    void checkFoundFlag();
public slots:

};

#endif // MCFINDER_H
