#ifndef MC3512SCANNER_H
#define MC3512SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3512Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3512Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
    void writeCycle() override;
};

#endif // MC3512SCANNER_H
