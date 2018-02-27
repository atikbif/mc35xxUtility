#ifndef TAB4DO_H
#define TAB4DO_H

#include <QtWidgets>

class Tab4DO
{
protected:
    QVector<QPushButton*> dOuts4;
public:
    Tab4DO();
    QWidget *create4DO();
    void setDO(bool value, QPushButton *button);
};

#endif // TAB4DO_H
