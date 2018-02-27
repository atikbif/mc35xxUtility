#include "abstractgui.h"

AbstractGUI::AbstractGUI(QWidget *parent) : QWidget(parent)
{

}

void AbstractGUI::readConfClicked()
{
    emit readConf();
}
