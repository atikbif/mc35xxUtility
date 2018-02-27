#include "mc3523gui.h"
#include "abstractscanner.h"


MC3523GUI::MC3523GUI(QWidget *parent):AbstractGUI(parent), TabAI8(), Tab2DOR(), TabConf(false,true,true)
{

}

QWidget *MC3523GUI::createWidget()
{
    QTabWidget *w = new QTabWidget();

    // configuration tab
    QWidget *confWidget = createConf();
    connect(buttonRead,SIGNAL(clicked(bool)),this,SLOT(readConfClicked()));
    connect(buttonWrite,SIGNAL(clicked(bool)),this,SLOT(writeConfClicked()));
    w->addTab(confWidget,"настройки");

    // adc tab
    QWidget *aiWidget = create8AI();
    w->addTab(aiWidget,"аналог. входы (мА)");

    // out tab
    QWidget *outWidget = create2DOR();
    foreach(QPushButton *out, dOuts2R) {
        connect(out,SIGNAL(clicked(bool)),this,SLOT(outClicked()));
    }
    w->addTab(outWidget,"рел. выходы");

    return w;
}

void MC3523GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterAI->setValue(conf.at(AbstractScanner::AI_FILTER));
        spinMaxNoLinkTime->setValue(conf.at(AbstractScanner::TIME_OUT_OFF));
        confPortDataToGui(conf);
    }
}

void MC3523GUI::ioData(QVector<quint16> io)
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
    if(io.count()>=10) {
        for(int i=0;i<2;i++) {
            if(i>=dOuts2R.count()) break;
            QPushButton *dout = dOuts2R.at(i);
            if(io.at(8+i)) setDO(true,dout); else setDO(false,dout);
        }
    }
}

void MC3523GUI::writeConfClicked()
{   
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::AI_FILTER] = spinFilterAI->value();
    cData[AbstractScanner::TIME_OUT_OFF] = spinMaxNoLinkTime->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3523GUI::outClicked()
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
