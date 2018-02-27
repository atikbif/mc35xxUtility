#ifndef MC3517GUI_H
#define MC3517GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tab8di.h"
#include "tab2ao.h"
#include "tabconf.h"

class MC3517GUI : public AbstractGUI, public Tab8DI, public Tab2AO, public TabConf
{
    Q_OBJECT
public:
    MC3517GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
    void writeAnOuts();
};

#endif // MC3517GUI_H
