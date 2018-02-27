#ifndef MC3556SCANNER_H
#define MC3556SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3556Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3556Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
};

#endif // MC3556SCANNER_H
