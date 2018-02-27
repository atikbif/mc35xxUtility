#ifndef ABSTRACTGUI_H
#define ABSTRACTGUI_H

#include <QObject>
#include <QWidget>
#include <QVector>

class AbstractGUI : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractGUI(QWidget *parent = 0);
    virtual QWidget* createWidget()=0;
signals:
    readConf();
    writeConf(QVector<quint16> conf);
    writeData(int num, quint16 value);
public slots:
    virtual void confData(QVector<quint16> conf)=0;
    virtual void ioData(QVector<quint16> io)=0;
protected slots:
    void readConfClicked();
};

#endif // ABSTRACTGUI_H
