#include "mc3525gui.h"
#include "abstractscanner.h"

MC3525GUI::MC3525GUI(QWidget *parent):AbstractGUI(parent), TabAI8(), TabConf(false,true,false)
{

}

QWidget *MC3525GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // ai8 tab
    QWidget *diWidget = create8AI();
    w->addTab(diWidget,"ан. вх (мА)");

    return w;
}

void MC3525GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterAI->setValue(conf.at(AbstractScanner::AI_FILTER));
        confPortDataToGui(conf);
    }
}

void MC3525GUI::ioData(QVector<quint16> io)
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

void MC3525GUI::writeConfClicked()
{
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::AI_FILTER] = spinFilterAI->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}
