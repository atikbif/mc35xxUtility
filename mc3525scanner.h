#ifndef MC3525SCANNER_H
#define MC3525SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3525Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3525Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
};

#endif // MC3525SCANNER_H
