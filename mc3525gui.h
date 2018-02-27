#ifndef MC3525GUI_H
#define MC3525GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tabai8.h"
#include "tabconf.h"

class MC3525GUI : public AbstractGUI, public TabAI8, public TabConf
{
    Q_OBJECT
public:
    MC3525GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
};

#endif // MC3525GUI_H
