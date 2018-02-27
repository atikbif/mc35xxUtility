#ifndef TAB2AO_H
#define TAB2AO_H

#include <QtWidgets>

class Tab2AO
{
protected:
    QSpinBox *dac1;
    QSpinBox *dac2;
public:
    Tab2AO();
    QWidget *create2AO();
};

#endif // TAB2AO_H
