#include "tab8do.h"

Tab8DO::Tab8DO()
{

}

QWidget *Tab8DO::create8DO()
{
    QWidget *outWidget = new QWidget();
    QGridLayout *outLayout = new QGridLayout();

    int row = 0;const int numInRow = 4;
    int num = 0;
    int doCount = 8;
    forever {
        for(int i=0;i<numInRow;i++) {
            num = row*numInRow + i;
            if(num<doCount) {
                QPushButton *out = new QPushButton(QString::number(num+1));
                dOuts8.append(out);
                out->setStyleSheet("border: 2px solid #8f8f91;border-radius: 20px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
                out->setFixedSize(40,40);
                outLayout->addWidget(out,row+1,i);
            }else break;
        }
        row++;
        if(num>=doCount) break;
    }
    //outLayout->addWidget(new QLabel(""),0,0);
    //outLayout->addWidget(new QLabel(""),row++,0);

    outWidget->setLayout(outLayout);
    return outWidget;
}

void Tab8DO::setDO(bool value, QPushButton *button)
{
    if(value) {
        button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 20px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #ff0000, stop: 1 #ffffff);");
        button->setToolTip("включен");
    }else {
        button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 20px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
        button->setToolTip("выключен");
    }
}
