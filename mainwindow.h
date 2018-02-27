#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <functional>
#include "abstractgui.h"
#include "linkmanager.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QVBoxLayout *widgetLayout;
    QSharedPointer<LinkManager> mLink;
    QSharedPointer<AbstractGUI> mGUI;
    int stopBits;
    int parity;
    quint32 baud;
    static std::map<QString,std::function<std::pair<QSharedPointer<LinkManager>,QSharedPointer<AbstractGUI>>(QString,int,qint32,int,int)>> mod_map;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    startScan();
    stopScan();

private slots:
    void on_pushButton_clicked();
    void updatePortList();
    void found();
    void info(QString value);
    void answerError();
    void correctAnswer(int cnt);

    void on_pushButtonStartStop_clicked();

private:
    Ui::MainWindow *ui;
    void showInfoWidget();
    void clearInfoWidget();
};

#endif // MAINWINDOW_H
