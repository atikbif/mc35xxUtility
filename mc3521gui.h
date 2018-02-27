#ifndef MC3521GUI_H
#define MC3521GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tab8do.h"
#include "tab2dor.h"
#include "tabconf.h"

class MC3521GUI : public AbstractGUI, public Tab8DO, public Tab2DOR, public TabConf
{
    Q_OBJECT

public:
    MC3521GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
};

#endif // MC3521GUI_H
