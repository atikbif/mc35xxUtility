#ifndef LINKMANAGER_H
#define LINKMANAGER_H

#include <QObject>
#include <QThread>
#include "abstractscanner.h"

class LinkManager: public QObject
{
    Q_OBJECT
    AbstractScanner *scanner;
    QThread scanThread;
public:
    explicit LinkManager(AbstractScanner *sc, QObject *parent=0);
    ~LinkManager();
signals:
    scanCycle();
    confData(QVector<quint16> conf);
    ioData(QVector<quint16> io);
    correctAnswer(int answerCounter);
    info(QString value);
    answerError();
public slots:
    void startScan();
    void stopScan();
    void readConf();
    void writeConf(QVector<quint16> conf);
    void writeData(int num, quint16 value);
};

#endif // LINKMANAGER_H
