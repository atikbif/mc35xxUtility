#include "tabai8.h"

TabAI8::TabAI8()
{

}

QWidget *TabAI8::create8AI()
{
    QWidget *dataWidget = new QWidget();
    QGridLayout *dataLayout = new QGridLayout();

    int row = 0;const int numInRow = 2;
    int num = 0;
    int aiCount = 8;
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
                a8Inputs.append(inp);

            }else break;
        }
        row++;
        if(num>=aiCount) break;
    }
    //dataLayout->addWidget(new QLabel(""),row++,0);

    dataWidget->setLayout(dataLayout);
    return dataWidget;
}
