#ifndef MC3516GUI_H
#define MC3516GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tabai8.h"
#include "tab2ao.h"
#include "tabconf.h"

class MC3516GUI : public AbstractGUI, public TabAI8, public Tab2AO, public TabConf
{
    Q_OBJECT
public:
    MC3516GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
    void writeAnOuts();
};

#endif // MC3516GUI_H
