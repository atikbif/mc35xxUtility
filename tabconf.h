#ifndef TABCONF_H
#define TABCONF_H

#include <QtWidgets>

class TabConf
{
    bool diFlag;
    bool aiFlag;
    bool outsFlag;
protected:
    QSpinBox *spinNetAddr;
    QSpinBox *spinFilterDI;
    QSpinBox *spinFilterAI;
    QSpinBox *spinMaxNoLinkTime;
    QLineEdit *editModVersion;
    QPushButton *buttonRead;
    QPushButton *buttonWrite;
    QComboBox *comboBoxBaud;
    QComboBox *comboBoxStopBits;
    QComboBox *comboBoxParity;
public:
    TabConf(bool di=false, bool ai=false, bool outs=false);
    void confPortDataToGui(const QVector<quint16> &conf);
    void GuiToConfPortData(QVector<quint16> &conf);
    QWidget *createConf();
};

#endif // TABCONF_H
