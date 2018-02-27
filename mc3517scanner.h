#ifndef MC3517SCANNER_H
#define MC3517SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3517Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3517Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
    void writeCycle() override;
};

#endif // MC3517SCANNER_H
