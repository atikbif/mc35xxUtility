#ifndef TAB8DI_H
#define TAB8DI_H

#include <QtWidgets>

class Tab8DI
{
protected:
    QVector<QPushButton*> dInputs8;
public:
    Tab8DI();
    QWidget *create8DI();
    void setDI(bool value, QPushButton *button);
};

#endif // TAB8DI_H
