#include "tab4di.h"

Tab4DI::Tab4DI()
{

}

QWidget *Tab4DI::create4DI()
{
    QWidget *dataWidget = new QWidget();
    QGridLayout *dataLayout = new QGridLayout();

    int row = 0;const int numInRow = 4;
    int num = 0;
    int diCount = 4;
    forever {
        for(int i=0;i<numInRow;i++) {
            num = row*numInRow + i;
            if(num<diCount) {
                QPushButton *inp = new QPushButton(QString::number(num+1));
                dInputs4.append(inp);
                inp->setStyleSheet("border: 2px solid #8f8f91;border-radius: 20px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
                inp->setFixedSize(40,40);
                dataLayout->addWidget(inp,row+1,i);
            }else break;
        }
        row++;
        if(num>=diCount) break;
    }
    dataLayout->addWidget(new QLabel(""),0,0);
    dataLayout->addWidget(new QLabel(""),row++,0);

    dataWidget->setLayout(dataLayout);
    return dataWidget;
}

void Tab4DI::setDI(bool value, QPushButton *button)
{
    if(value) button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 20px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #00ff00, stop: 1 #ffffff);");
    else button->setStyleSheet("border: 2px solid #8f8f91;border-radius: 20px;background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #f6f7fa, stop: 1 #dadbde);");
}
