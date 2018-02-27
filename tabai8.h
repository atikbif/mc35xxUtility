#ifndef TABAI8_H
#define TABAI8_H

#include <QtWidgets>

class TabAI8
{
protected:
    QVector<QLCDNumber*> a8Inputs;
public:
    TabAI8();
    QWidget* create8AI();
};

#endif // TABAI8_H
