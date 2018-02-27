#ifndef MC3512GUI_H
#define MC3512GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tab8di.h"
#include "tab8do.h"
#include "tabconf.h"

class MC3512GUI : public AbstractGUI, public Tab8DI, public Tab8DO, public TabConf
{
    Q_OBJECT
public:
    MC3512GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
};

#endif // MC3512GUI_H
