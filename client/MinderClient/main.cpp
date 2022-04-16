#include <QApplication>
#include <QDebug>

#include "screencontroller.h"
#include "logiccontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LogicController lc;

    return a.exec();
}
