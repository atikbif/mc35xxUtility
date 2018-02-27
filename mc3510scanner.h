#ifndef MC3510SCANNER_H
#define MC3510SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3510Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3510Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
};

#endif // MC3510SCANNER_H
