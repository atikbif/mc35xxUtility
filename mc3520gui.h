#ifndef MC3520GUI_H
#define MC3520GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tab8di.h"
#include "tab2dor.h"
#include "tabconf.h"

class MC3520GUI : public AbstractGUI, public Tab8DI, public Tab2DOR, public TabConf
{
    Q_OBJECT

public:
    MC3520GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
};

#endif // MC3520GUI_H
