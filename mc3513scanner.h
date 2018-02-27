#ifndef MC3513SCANNER_H
#define MC3513SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3513Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3513Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
};

#endif // MC3513SCANNER_H
