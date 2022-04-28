#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QDir>

#include "ScreenController.h"
#include "LogicController.h"

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

    LogicController lc;

    return a.exec();
}
