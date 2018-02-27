#ifndef TABAI16_H
#define TABAI16_H

#include <QtWidgets>

class TabAI16
{
protected:
    QVector<QLCDNumber*> a16Inputs;
public:
    TabAI16();
    QWidget* create16AI();
};

#endif // TABAI16_H
