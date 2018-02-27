#ifndef TAB16DO_H
#define TAB16DO_H

#include <QtWidgets>

class Tab16DO
{
protected:
    QVector<QPushButton*> dOuts16;
public:
    Tab16DO();
    QWidget *create16DO();
    void setDO(bool value, QPushButton *button);
};

#endif // TAB16DO_H
