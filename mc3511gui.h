#ifndef MC3511GUI_H
#define MC3511GUI_H

#include "abstractgui.h"
#include <QtWidgets>
#include "tab16do.h"
#include "tabconf.h"
#include <QTimer>

class MC3511GUI : public AbstractGUI, public Tab16DO, public TabConf
{
    Q_OBJECT
public:
    MC3511GUI(QWidget *parent = 0);
    QWidget* createWidget();
public slots:
    void confData(QVector<quint16> conf);
    void ioData(QVector<quint16> io);
private slots:
    void writeConfClicked();
    void outClicked();
};

#endif // MC3511GUI_H
