#include "mc3518gui.h"
#include "abstractscanner.h"

MC3518GUI::MC3518GUI(QWidget *parent):AbstractGUI(parent), Tab8DO(), Tab2AO(), TabConf(false,false,true)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(writeAnOuts()));
    timer->start(200);
}

QWidget *MC3518GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // do8 tab
    QWidget *doWidget = create8DO();
    foreach(QPushButton *out, dOuts8) {
        connect(out,SIGNAL(clicked(bool)),this,SLOT(outClicked()));
    }
    w->addTab(doWidget,"дискр. вых");

    // ao2 tab
    QWidget *outWidget = create2AO();
    w->addTab(outWidget,"аналог. вых");

    return w;
}

void MC3518GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinMaxNoLinkTime->setValue(conf.at(AbstractScanner::TIME_OUT_OFF));
        confPortDataToGui(conf);
    }
}

void MC3518GUI::ioData(QVector<quint16> io)
{
    if(io.count()>=1) {
        for(int i=0;i<8;i++) {
            if(i>=dOuts8.count()) break;
            QPushButton *dout = dOuts8.at(i);
            if(io.at(0) & (1<<i)) setDO(true,dout);else setDO(false,dout);
        }
    }
}

void MC3518GUI::writeConfClicked()
{   
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::TIME_OUT_OFF] = spinMaxNoLinkTime->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3518GUI::outClicked()
{
    QPushButton *button = dynamic_cast<QPushButton*>(sender());
    if(button!=nullptr) {
        for(int i=0;i<dOuts8.count();i++) {
            if(button==dOuts8.at(i)) {
                // toggle cmd
                if(button->toolTip().contains("вкл")) emit writeData(i+2,0);
                else emit writeData(i+2,1);
                timer->start(200);
                break;
            }
        }
    }
}

void MC3518GUI::writeAnOuts()
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
