#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QDir>

#include "LogicController.h"
#include "HttpClient.hpp"


#include <QThread>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Загружаем qss файл
    QFile qssFile(":/styles/qss/global.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        QString qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    else
    {
        qDebug() << "Error: " << qssFile.errorString();
    }

    HttpClient *httpClient = new HttpClient(std::string("localhost"), 7777);
    LogicController lc(httpClient);
    QThread logicThread;
    lc.moveToThread(&logicThread);
    logicThread.start();


    a.exec();


    logicThread.quit();
    logicThread.wait();


    return EXIT_SUCCESS;
}
