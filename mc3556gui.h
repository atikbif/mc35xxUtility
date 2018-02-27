#ifndef MC3556GUI_H
#define MC3556GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tabai16.h"
#include "tabconf.h"

class MC3556GUI : public AbstractGUI, public TabAI16, public TabConf
{
    Q_OBJECT
public:
    MC3556GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
};

#endif // MC3556GUI_H
