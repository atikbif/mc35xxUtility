#include "mc3516gui.h"
#include <QTimer>
#include "abstractscanner.h"

MC3516GUI::MC3516GUI(QWidget *parent):AbstractGUI(parent), TabAI8(), Tab2AO(), TabConf(false,true,true)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(writeAnOuts()));
    timer->start(150);
}

QWidget *MC3516GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // ai8 tab
    QWidget *diWidget = create8AI();
    w->addTab(diWidget,"аналог. вх (мА)");

    // ao2 tab
    QWidget *outWidget = create2AO();
    w->addTab(outWidget,"аналог. вых");

    return w;
}

void MC3516GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterAI->setValue(conf.at(AbstractScanner::AI_FILTER));
        spinMaxNoLinkTime->setValue(conf.at(AbstractScanner::TIME_OUT_OFF));
        confPortDataToGui(conf);
    }
}

void MC3516GUI::ioData(QVector<quint16> io)
{
    if(io.count()>=8) {
        for(int i=0;i<8;i++) {
            if(i<=a8Inputs.count()) {
                QLCDNumber *inp = a8Inputs.at(i);
                double value = (((double)(io.at(i)))*20/4096)*1;//1.041;
                QString str = QString::number(value,'f',2);
                inp->display(str);
            }
        }
    }
}

void MC3516GUI::writeConfClicked()
{  
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::AI_FILTER] = spinFilterAI->value();
    cData[AbstractScanner::TIME_OUT_OFF] = spinMaxNoLinkTime->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3516GUI::outClicked()
{

}

void MC3516GUI::writeAnOuts()
{
    static quint16 cnt = 0;
    const quint16 maxValue = 65535;
    cnt++;
    if(cnt&0x01) {
        quint16 regValue = ((double)maxValue/20)*dac1->value()+0.5;
        writeData(0,regValue);
    }else {
        quint16 regValue = ((double)maxValue/20)*dac2->value()+0.5;
        writeData(1,regValue);
    }
}
