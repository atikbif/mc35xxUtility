#ifndef MC3523GUI_H
#define MC3523GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tabai8.h"
#include "tab2dor.h"
#include "tabconf.h"

class MC3523GUI : public AbstractGUI, public TabAI8, public Tab2DOR, public TabConf
{
    Q_OBJECT

public:
    MC3523GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
};

#endif // MC3523GUI_H
