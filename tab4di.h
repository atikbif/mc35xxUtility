#ifndef TAB4DI_H
#define TAB4DI_H

#include <QtWidgets>

class Tab4DI
{
protected:
    QVector<QPushButton*> dInputs4;
public:
    Tab4DI();
    QWidget *create4DI();
    void setDI(bool value, QPushButton *button);
};

#endif // TAB4DI_H
