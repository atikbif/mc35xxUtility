#ifndef FINDERTHREAD_H
#define FINDERTHREAD_H

#include <QObject>
#include <QString>
#include <QMutexLocker>

class FinderThread : public QObject
{
    Q_OBJECT
    QString portName;
    bool stopFlag;
    QMutex mutex;
    int netAddress;

    QString getModNameByID(const QVector<quint8> id);
    bool startSearchWithPortConf(quint8 stopBits, quint8 parity,double startPercent, double percentDelta);
    static QVector<qint32> baudTable;


public:
    explicit FinderThread(const QString &pName, int netAddr=0, QObject *parent = 0);

signals:
    percentUpdate(QString pName, double value);
    found(QString pName, int baudRate, int stopBits, int parity, int netAddr, QString modName);
    failed(QString pName);
public slots:
    void startSearch();
    void stopSearch();
};

#endif // FINDERTHREAD_H
