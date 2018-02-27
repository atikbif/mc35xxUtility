#include "tabai16.h"

TabAI16::TabAI16()
{

}

QWidget *TabAI16::create16AI()
{
    QWidget *dataWidget = new QWidget();
    QGridLayout *dataLayout = new QGridLayout();

    int row = 0;const int numInRow = 4;
    int num = 0;
    int aiCount = 16;
    forever {
        for(int i=0;i<numInRow;i++) {
            num = row*numInRow + i;
            if(num<aiCount) {
                QLCDNumber *inp = new QLCDNumber(7);
                inp->setStyleSheet("background-color: black;");
                inp->setPalette(Qt::white);
                inp->setFixedSize(80,40);
                inp->setToolTip("ADC"+QString::number(num+1));
                QHBoxLayout *hBox = new QHBoxLayout();
                hBox->addStretch();
                hBox->addWidget(new QLabel(QString::number(num+1)+":"));
                hBox->addWidget(inp,1);
                hBox->addStretch();
                //dataLayout->addWidget(inp,row+1,i);
                dataLayout->addLayout(hBox,row+1,i);
                a16Inputs.append(inp);

            }else break;
        }
        row++;
        if(num>=aiCount) break;
    }
    //dataLayout->addWidget(new QLabel(""),row++,0);

    dataWidget->setLayout(dataLayout);
    return dataWidget;
}
