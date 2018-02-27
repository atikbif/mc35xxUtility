#include "mc3521gui.h"
#include "abstractscanner.h"


MC3521GUI::MC3521GUI(QWidget *parent):AbstractGUI(parent), Tab8DO(), Tab2DOR(), TabConf(false,false,true)
{

}

QWidget *MC3521GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // do8 tab
    QWidget *do8Widget = create8DO();
    foreach(QPushButton *out, dOuts8) {
        connect(out,SIGNAL(clicked(bool)),this,SLOT(outClicked()));
    }
    w->addTab(do8Widget,"дискр. вых");

    // do2R tab
    QWidget *do2RWidget = create2DOR();
    foreach(QPushButton *out, dOuts2R) {
        connect(out,SIGNAL(clicked(bool)),this,SLOT(outClicked()));
    }
    w->addTab(do2RWidget,"рел. выходы");

    return w;
}

void MC3521GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinMaxNoLinkTime->setValue(conf.at(AbstractScanner::TIME_OUT_OFF));
        confPortDataToGui(conf);
    }
}

void MC3521GUI::ioData(QVector<quint16> io)
{
    if(io.count()>=1) {
        for(int i=0;i<8;i++) {
            if(i>=dOuts8.count()) break;
            QPushButton *dout = dOuts8.at(i);
            if(io.at(0) & (1 << i)) Tab8DO::setDO(true,dout); else Tab8DO::setDO(false,dout);
        }
        for(int i=0;i<2;i++) {
            if(i>=dOuts2R.count()) break;
            QPushButton *dout = dOuts2R.at(i);
            if(io.at(0) & (1 << (8+i))) Tab2DOR::setDO(true,dout); else Tab2DOR::setDO(false,dout);
        }
    }
}

void MC3521GUI::writeConfClicked()
{   
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::TIME_OUT_OFF] = spinMaxNoLinkTime->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3521GUI::outClicked()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    if(button!=nullptr) {
        for(int i=0;i<dOuts8.count();i++) {
            if(button==dOuts8.at(i)) {
                // toggle cmd
                if(button->toolTip().contains("вкл")) emit writeData(i,0);
                else emit writeData(i,1);
                break;
            }
        }
        for(int i=0;i<dOuts2R.count();i++) {
            if(button==dOuts2R.at(i)) {
                // toggle cmd
                if(button->toolTip().contains("вкл")) emit writeData(i+8,0);
                else emit writeData(i+8,1);
                break;
            }
        }
    }
}
