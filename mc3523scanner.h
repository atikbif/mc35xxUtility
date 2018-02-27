#ifndef MC3523SCANNER_H
#define MC3523SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3523Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3523Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
    void writeCycle() override;
};

#endif // MC3523SCANNER_H
