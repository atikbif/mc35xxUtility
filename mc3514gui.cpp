#include "mc3514gui.h"
#include "abstractscanner.h"

MC3514GUI::MC3514GUI(QWidget *parent):AbstractGUI(parent), TabAI8(), Tab8DO(), TabConf(false,true,true)
{

}

QWidget *MC3514GUI::createWidget()
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

    // do8 tab
    QWidget *outWidget = create8DO();
    foreach(QPushButton *out, dOuts8) {
        connect(out,SIGNAL(clicked(bool)),this,SLOT(outClicked()));
    }
    w->addTab(outWidget,"дискр. вых");

    return w;
}

void MC3514GUI::confData(QVector<quint16> conf)
{
    if(conf.count()>=AbstractScanner::confLength+1) {
        spinNetAddr->setValue(conf.at(AbstractScanner::NET_ADDR));
        spinFilterAI->setValue(conf.at(AbstractScanner::AI_FILTER));
        spinMaxNoLinkTime->setValue(conf.at(AbstractScanner::TIME_OUT_OFF));
        confPortDataToGui(conf);
    }
}

void MC3514GUI::ioData(QVector<quint16> io)
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
    if(io.count()>=9) {
        for(int i=0;i<8;i++) {
            if(i>=dOuts8.count()) break;
            QPushButton *dout = dOuts8.at(i);
            if(io.at(8) & (1<<i)) setDO(true,dout);else setDO(false,dout);
        }
    }
}

void MC3514GUI::writeConfClicked()
{
    QVector<quint16> cData = AbstractScanner::getEmptyConf();
    cData[AbstractScanner::NET_ADDR] = spinNetAddr->value();
    cData[AbstractScanner::AI_FILTER] = spinFilterAI->value();
    cData[AbstractScanner::TIME_OUT_OFF] = spinMaxNoLinkTime->value();
    GuiToConfPortData(cData);
    emit writeConf(cData);
}

void MC3514GUI::outClicked()
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
    }
}
