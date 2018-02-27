#include "mc3520gui.h"
#include "abstractscanner.h"


MC3520GUI::MC3520GUI(QWidget *parent):AbstractGUI(parent), Tab8DI(), Tab2DOR(), TabConf(true,false,true)
{

}

QWidget *MC3520GUI::createWidget()
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

    // out tab
    QWidget *outWidget = create2DOR();
    foreach(QPushButton *out, dOuts2R) {
        connect(out,SIGNAL(clicked(bool)),this,SLOT(outClicked()));
    }
    w->addTab(outWidget,"рел. выходы");

    return w;
}

void MC3520GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterDI->setValue(conf.at(AbstractScanner::DI_FILTER));
        spinMaxNoLinkTime->setValue(conf.at(AbstractScanner::TIME_OUT_OFF));
        confPortDataToGui(conf);
    }
}

void MC3520GUI::ioData(QVector<quint16> io)
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
    if(io.count()>=3) {
        for(int i=0;i<2;i++) {
            if(i>=dOuts2R.count()) break;
            QPushButton *dout = dOuts2R.at(i);
            if(io.at(1+i)) setDO(true,dout); else setDO(false,dout);
        }
    }
}

void MC3520GUI::writeConfClicked()
{   
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::DI_FILTER] = spinFilterDI->value();
    cData[AbstractScanner::TIME_OUT_OFF] = spinMaxNoLinkTime->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3520GUI::outClicked()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    if(button!=nullptr) {
        for(int i=0;i<dOuts2R.count();i++) {
            if(button==dOuts2R.at(i)) {
                // toggle cmd
                if(button->toolTip().contains("вкл")) emit writeData(i,0);
                else emit writeData(i,1);
                break;
            }
        }
    }
}
