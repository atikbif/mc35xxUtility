#ifndef MC3514SCANNER_H
#define MC3514SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3514Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3514Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
    void writeCycle() override;
};

#endif // MC3514SCANNER_H
