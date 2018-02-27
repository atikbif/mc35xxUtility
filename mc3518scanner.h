#ifndef MC3518SCANNER_H
#define MC3518SCANNER_H

#include <QObject>
#include "abstractscanner.h"

class MC3518Scanner : public AbstractScanner
{
    Q_OBJECT

public:
    explicit MC3518Scanner(const QString &pName, int netAddr, qint32 baudrate, int stopBits, int parity, QObject *parent = 0);
private:
    void readCycle() override;
    void writeCycle() override;
};

#endif // MC3518SCANNER_H
