#ifndef MC3510GUI_H
#define MC3510GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tab16di.h"
#include "tabconf.h"

class MC3510GUI : public AbstractGUI, public Tab16DI, public TabConf
{
    Q_OBJECT
public:
    MC3510GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
};

#endif // MC3510GUI_H
