#ifndef TAB8DO_H
#define TAB8DO_H

#include <QtWidgets>

class Tab8DO
{
protected:
    QVector<QPushButton*> dOuts8;
public:
    Tab8DO();
    QWidget *create8DO();
    void setDO(bool value, QPushButton *button);
};

#endif // TAB8DO_H
