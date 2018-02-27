#ifndef MC3513GUI_H
#define MC3513GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tabai8.h"
#include "tab8di.h"
#include "tabconf.h"

class MC3513GUI : public AbstractGUI, public TabAI8, public Tab8DI, public TabConf
{
    Q_OBJECT
public:
    MC3513GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
};

#endif // MC3513GUI_H
