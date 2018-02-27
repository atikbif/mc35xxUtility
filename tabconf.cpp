#include "tabconf.h"
#include "abstractscanner.h"

TabConf::TabConf(bool di, bool ai, bool outs):diFlag(di),aiFlag(ai),outsFlag(outs)
{

}

void TabConf::GuiToConfPortData(QVector<quint16> &conf)
{
    if(conf.length()>=AbstractScanner::confLength) {
        conf[AbstractScanner::BAUD]=comboBoxBaud->currentIndex();
        if(comboBoxStopBits->currentText()=="1") conf[AbstractScanner::STOP_BITS]=0;else conf[AbstractScanner::STOP_BITS]=1;
        conf[AbstractScanner::PARITY]=comboBoxParity->currentIndex();
    }
}

void TabConf::confPortDataToGui(const QVector<quint16> &conf)
{
    if((conf.at(7)>>8)==1) { // если модуль версии 1.x (фиксированная скорость 115200 и формат байта 8N1)
        comboBoxBaud->setCurrentText("115200");
        comboBoxBaud->setEnabled(false);
        comboBoxStopBits->setCurrentText("1");
        comboBoxStopBits->setEnabled(false);
        comboBoxParity->setCurrentText("нет");
        comboBoxParity->setEnabled(false);
    }else { // модуль допускает настройку скорости и формата байта
        switch(conf.at(AbstractScanner::BAUD)) {
            case 0:comboBoxBaud->setCurrentText("115200");break;
            case 1:comboBoxBaud->setCurrentText("57600");break;
            case 2:comboBoxBaud->setCurrentText("38400");break;
            case 3:comboBoxBaud->setCurrentText("19200");break;
            case 4:comboBoxBaud->setCurrentText("9600");break;
            default:comboBoxBaud->setCurrentText("115200");break;
        }
        comboBoxBaud->setEnabled(true);
        switch(conf.at(AbstractScanner::STOP_BITS)) {
            case 0:comboBoxStopBits->setCurrentText("1");break;
            case 1:comboBoxStopBits->setCurrentText("2");break;
            default:comboBoxStopBits->setCurrentText("1");break;
        }
        comboBoxStopBits->setEnabled(true);

        switch(conf.at(AbstractScanner::PARITY)) {
            case 0:comboBoxParity->setCurrentText("нет");break;
            case 1:comboBoxParity->setCurrentText("ODD");break;
            case 2:comboBoxParity->setCurrentText("EVEN");break;
            default:comboBoxParity->setCurrentText("нет");break;
        }
        comboBoxParity->setEnabled(true);
    }


    editModVersion->setText(QString::number(conf.at(7)>>8)+"."+QString::number(conf.at(7)&0xFF));
}

QWidget *TabConf::createConf()
{
    QWidget *confWidget = new QWidget();
    QGridLayout *confLayout = new QGridLayout();
    int rowNum = 1;

    spinNetAddr = new QSpinBox();
    spinNetAddr->setMinimum(0);
    spinNetAddr->setMaximum(255);
    confLayout->addWidget(new QLabel("Сетевой адрес:"),rowNum,0);
    confLayout->addWidget(spinNetAddr,rowNum++,1);

    comboBoxBaud = new QComboBox();
    comboBoxBaud->addItems({"115200","57600","38400","19200","9600"});
    confLayout->addWidget(new QLabel("Скорость порта:"),rowNum,0);
    confLayout->addWidget(comboBoxBaud,rowNum++,1);

    comboBoxStopBits = new QComboBox();
    comboBoxStopBits->addItems({"1","2"});
    confLayout->addWidget(new QLabel("Число стоп бит:"),rowNum,0);
    confLayout->addWidget(comboBoxStopBits,rowNum++,1);

    comboBoxParity = new QComboBox();
    comboBoxParity->addItems({"нет","ODD","EVEN"});
    confLayout->addWidget(new QLabel("Бит чётности:"),rowNum,0);
    confLayout->addWidget(comboBoxParity,rowNum++,1);

    if(diFlag) {
        spinFilterDI = new QSpinBox();
        spinFilterDI->setMinimum(0);
        spinFilterDI->setMaximum(600);
        confLayout->addWidget(new QLabel("Фильтр дискр.вх(0.01 с):"),rowNum,0);
        confLayout->addWidget(spinFilterDI,rowNum++,1);
    }

    if(aiFlag) {
        spinFilterAI = new QSpinBox();
        spinFilterAI->setMinimum(0);
        spinFilterAI->setMaximum(600);
        confLayout->addWidget(new QLabel("Фильтр АЦП (0.01 с):"),rowNum,0);
        confLayout->addWidget(spinFilterAI,rowNum++,1);
    }

    if(outsFlag) {
        spinMaxNoLinkTime = new QSpinBox();
        spinMaxNoLinkTime->setMinimum(1);
        spinMaxNoLinkTime->setMaximum(100);
        confLayout->addWidget(new QLabel("Макс. интервал опроса (с):"));
        confLayout->addWidget(spinMaxNoLinkTime,rowNum++,1);
    }


    editModVersion = new QLineEdit();
    editModVersion->setReadOnly(true);
    confLayout->addWidget(new QLabel("Версия модуля:"));
    confLayout->addWidget(editModVersion,rowNum++,1);


    buttonRead = new QPushButton("Прочитать");
    buttonWrite = new QPushButton("Записать");
    confLayout->addWidget(buttonRead,rowNum+2,0);
    confLayout->addWidget(buttonWrite,rowNum+2,1);
    confLayout->addWidget(new QLabel(),rowNum,0,1,2);

    confLayout->setColumnStretch(0,1);
    confLayout->setColumnStretch(1,1);

    confWidget->setLayout(confLayout);
    return confWidget;
}
