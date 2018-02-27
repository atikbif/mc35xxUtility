#ifndef TAB2DOR_H
#define TAB2DOR_H

#include <QtWidgets>

class Tab2DOR
{
protected:
    QVector<QPushButton*> dOuts2R;
public:
    Tab2DOR();
    QWidget *create2DOR();
    void setDO(bool value, QPushButton *button);
};

#endif // TAB2DOR_H
