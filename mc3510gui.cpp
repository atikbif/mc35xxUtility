#include "mc3510gui.h"
#include "abstractscanner.h"


MC3510GUI::MC3510GUI(QWidget *parent):AbstractGUI(parent), Tab16DI(), TabConf(true,false,false)
{

}

QWidget *MC3510GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // data tab
    QWidget *dataWidget = create16DI();
    w->addTab(dataWidget,"дискр. входы");
    return w;
}

void MC3510GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) { // настройки + версия модуля
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterDI->setValue(conf.at(AbstractScanner::DI_FILTER));
        confPortDataToGui(conf);
    }
}

void MC3510GUI::ioData(QVector<quint16> io)
{
    if(io.count()>=1) {
        for(int i=0;i<16;i++) {
            if(i<=dInputs16.count()) {
                bool bitValue = io.at(0) & (1<<i);
                QPushButton *inp = dInputs16.at(i);
                setDI(bitValue,inp);
            }
        }
    }
}


void MC3510GUI::writeConfClicked()
{
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::DI_FILTER] = spinFilterDI->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}
