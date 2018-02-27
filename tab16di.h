#ifndef TAB16DI_H
#define TAB16DI_H

#include <QtWidgets>

class Tab16DI
{
protected:
    QVector<QPushButton*> dInputs16;
public:
    Tab16DI();
    QWidget *create16DI();
    void setDI(bool value, QPushButton *button);
};

#endif // TAB16DI_H
