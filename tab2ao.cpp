#include "tab2ao.h"

Tab2AO::Tab2AO()
{

}

QWidget *Tab2AO::create2AO()
{
    QWidget *outWidget = new QWidget();

    QGroupBox *box1 = new QGroupBox("Выход 1 (мА)");
    QGroupBox *box2 = new QGroupBox("Выход 2 (мА)");

    dac1 = new QSpinBox();
    dac1->setMinimum(4);
    dac1->setMaximum(20);

    dac2 = new QSpinBox();
    dac2->setMinimum(4);
    dac2->setMaximum(20);



    QVBoxLayout *vBox1Layout = new QVBoxLayout();
    QVBoxLayout *vBox2Layout = new QVBoxLayout();

    vBox1Layout->addWidget(dac1);
    vBox2Layout->addWidget(dac2);

    box1->setLayout(vBox1Layout);
    box2->setLayout(vBox2Layout);

    QVBoxLayout *vLayout = new QVBoxLayout();
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch();
    hLayout->addWidget(box1);
    hLayout->addStretch();
    hLayout->addWidget(box2);
    hLayout->addStretch();
    vLayout->addStretch();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();

    outWidget->setLayout(vLayout);
    return outWidget;
}
