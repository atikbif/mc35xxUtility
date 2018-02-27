#include "mc3511gui.h"
#include "abstractscanner.h"

MC3511GUI::MC3511GUI(QWidget *parent):AbstractGUI(parent), Tab16DO(), TabConf(false,false,true)
{
}

QWidget *MC3511GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // do16 tab
    QWidget *doWidget = create16DO();
    foreach(QPushButton *out, dOuts16) {
        connect(out,SIGNAL(clicked(bool)),this,SLOT(outClicked()));
    }
    w->addTab(doWidget,"дискр. вых");

    return w;
}

void MC3511GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) { // настройки + версия модуля
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinMaxNoLinkTime->setValue(conf.at(AbstractScanner::TIME_OUT_OFF));
        confPortDataToGui(conf);
    }
}

void MC3511GUI::ioData(QVector<quint16> io)
{
    if(io.count()>=1) {
        for(int i=0;i<16;i++) {
            if(i>=dOuts16.count()) break;
            QPushButton *dout = dOuts16.at(i);
            if(io.at(0) & (1<<i)) setDO(true,dout);else setDO(false,dout);
        }
    }
}

void MC3511GUI::writeConfClicked()
{   
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::TIME_OUT_OFF] = spinMaxNoLinkTime->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3511GUI::outClicked()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    if(button!=nullptr) {
        for(int i=0;i<dOuts16.count();i++) {
            if(button==dOuts16.at(i)) {
                // toggle cmd
                if(button->toolTip().contains("вкл")) emit writeData(i,0);
                else emit writeData(i,1);
                break;
            }
        }
    }
}

