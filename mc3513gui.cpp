#include "mc3513gui.h"
#include "abstractscanner.h"

MC3513GUI::MC3513GUI(QWidget *parent):AbstractGUI(parent), TabAI8(), Tab8DI(), TabConf(true,true,false)
{

}

QWidget *MC3513GUI::createWidget()
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

    // di8 tab
    QWidget *outWidget = create8DI();
    w->addTab(outWidget,"дискр. вх");

    return w;
}

void MC3513GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterDI->setValue(conf.at(AbstractScanner::DI_FILTER));
        spinFilterAI->setValue(conf.at(AbstractScanner::AI_FILTER));
        confPortDataToGui(conf);
    }
}

void MC3513GUI::ioData(QVector<quint16> io)
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
    if(io.count()>=9) {
        for(int i=0;i<8;i++) {
            if(i<=a8Inputs.count()) {
                QLCDNumber *inp = a8Inputs.at(i);
                double value = (((double)(io.at(i+1)))*20/4096)*1;//1.041;
                QString str = QString::number(value,'f',2);
                inp->display(str);
            }
        }
    }
}

void MC3513GUI::writeConfClicked()
{  
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::DI_FILTER] = spinFilterDI->value();
    cData[AbstractScanner::AI_FILTER] = spinFilterAI->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3513GUI::outClicked()
{
}
