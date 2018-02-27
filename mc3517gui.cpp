#include "mc3517gui.h"
#include <QTimer>
#include "abstractscanner.h"

MC3517GUI::MC3517GUI(QWidget *parent):AbstractGUI(parent), Tab8DI(), Tab2AO(), TabConf(true,false,true)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(writeAnOuts()));
    timer->start(150);
}

QWidget *MC3517GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // di8 tab
    QWidget *diWidget = create8DI();
    w->addTab(diWidget,"дискр. вх");

    // ao2 tab
    QWidget *outWidget = create2AO();
    w->addTab(outWidget,"аналог. вых");

    return w;
}

void MC3517GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterDI->setValue(conf.at(AbstractScanner::DI_FILTER));
        spinMaxNoLinkTime->setValue(conf.at(AbstractScanner::TIME_OUT_OFF));
        confPortDataToGui(conf);
    }
}

void MC3517GUI::ioData(QVector<quint16> io)
{
    if(io.count()>=1) {
        for(int i=0;i<8;i++) {
            if(i<=dInputs8.count()) {
                bool bitValue = io.at(0) & (1<<i);
                QPushButton *inp = dInputs8.at(i);
                setDI(bitValue,inp);
            }
        }
    }
}

void MC3517GUI::writeConfClicked()
{
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::DI_FILTER] = spinFilterDI->value();
    cData[AbstractScanner::TIME_OUT_OFF] = spinMaxNoLinkTime->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3517GUI::outClicked()
{

}

void MC3517GUI::writeAnOuts()
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
