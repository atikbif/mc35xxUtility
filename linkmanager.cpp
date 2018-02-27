#include "linkmanager.h"

LinkManager::LinkManager(AbstractScanner *sc, QObject *parent):QObject(parent),scanner(sc)
{
    scanner->moveToThread(&scanThread);
    connect(&scanThread,&QThread::finished,scanner,&AbstractScanner::deleteLater);
    connect(this,&LinkManager::scanCycle,scanner,&AbstractScanner::scanCycle);
    connect(scanner,&AbstractScanner::confData,this,&LinkManager::confData);
    connect(scanner,&AbstractScanner::ioData,this,&LinkManager::ioData);
    connect(scanner,&AbstractScanner::answerError,this,&LinkManager::answerError);
    connect(scanner,&AbstractScanner::correctAnswer,this,&LinkManager::correctAnswer);
    connect(scanner,&AbstractScanner::info,this,&LinkManager::info);
    scanThread.start();
    emit scanCycle();
}

LinkManager::~LinkManager()
{
    scanner->finishProcess();
    scanThread.quit();
    scanThread.wait();
}

void LinkManager::startScan()
{
    scanner->startScan();
}

void LinkManager::stopScan()
{
    scanner->stopScan();
}

void LinkManager::readConf()
{
    scanner->readConf();
}

void LinkManager::writeConf(QVector<quint16> conf)
{
    scanner->writeConf(conf);
}

void LinkManager::writeData(int num, quint16 value)
{
    scanner->writeData(num,value);
}
