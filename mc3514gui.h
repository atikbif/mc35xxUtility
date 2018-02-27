#ifndef MC3514GUI_H
#define MC3514GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tabai8.h"
#include "tab8do.h"
#include "tabconf.h"

class MC3514GUI : public AbstractGUI, public TabAI8, public Tab8DO, public TabConf
{
    Q_OBJECT
public:
    MC3514GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
};

#endif // MC3514GUI_H
