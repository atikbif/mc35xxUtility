#ifndef MC3518GUI_H
#define MC3518GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tab8do.h"
#include "tab2ao.h"
#include "tabconf.h"
#include <QTimer>

class MC3518GUI : public AbstractGUI, public Tab8DO, public Tab2AO, public TabConf
{
    Q_OBJECT
    QTimer *timer;
public:
    MC3518GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
    void writeAnOuts();
};

#endif // MC3518GUI_H
