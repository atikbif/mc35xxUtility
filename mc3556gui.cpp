#include "mc3556gui.h"
#include "abstractscanner.h"

MC3556GUI::MC3556GUI(QWidget *parent):AbstractGUI(parent), TabAI16(), TabConf(false,true,false)
{

}

QWidget *MC3556GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // ai16 tab
    QWidget *diWidget = create16AI();
    w->addTab(diWidget,"ан. вх (мА)");

    return w;
}

void MC3556GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterAI->setValue(conf.at(AbstractScanner::AI_FILTER));
        confPortDataToGui(conf);
    }
}

void MC3556GUI::ioData(QVector<quint16> io)
{
    if(io.count()>=16) {
        for(int i=0;i<16;i++) {
            if(i<=a16Inputs.count()) {
                QLCDNumber *inp = a16Inputs.at(i);
                double value = (((double)(io.at(i)))*20/4096)*1;//1.041;
                QString str = QString::number(value,'f',2);
                inp->display(str);
            }
        }
    }
}

void MC3556GUI::writeConfClicked()
{
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::AI_FILTER] = spinFilterAI->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}
