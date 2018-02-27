#include "tab2dor.h"

Tab2DOR::Tab2DOR()
{

}

QWidget *Tab2DOR::create2DOR()
{
    QWidget *outWidget = new QWidget();
    QGridLayout *outLayout = new QGridLayout();

    int row = 0;const int numInRow = 4;
    int num = 0;
    int doCount = 2;
    forever {
        for(int i=0;i<numInRow;i++) {
            num = row*numInRow + i;
            if(num<doCount) {
                QPushButton *out = new QPushButton(QString::number(num+1));
                //connect(out,SIGNAL(clicked(bool)),this,SLOT(outClicked()));
                dOuts2R.append(out);
                out->setStyleSheet("border: 2px solid #8f8f91;border-radius: 30px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
                out->setFixedSize(60,60);
                outLayout->addWidget(out,row+1,i);
            }else break;
        }
        row++;
        if(num>=doCount) break;
    }
    //connect(startStopButtonDO2R,SIGNAL(clicked(bool)),this,SLOT(startStopClicked()));
    outWidget->setLayout(outLayout);
    return outWidget;
}

void Tab2DOR::setDO(bool value, QPushButton *button)
{
    if(value) {
        button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 30px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ff0000, stop: 1 #ffffff);");
        button->setToolTip("включен");
    }else {
        button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 30px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
        button->setToolTip("выключен");
    }
}
