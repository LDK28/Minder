#include <QObject>
#include <QTest>

#include "ScreenController.h"
#include "DataStructures.h"

class test_ScreenController : public QObject
{
    Q_OBJECT
public:
    explicit test_ScreenController(QObject *parent = 0) : QObject(parent) {}

private slots: // должны быть приватными
    void test_Login();
    
};


void test_ScreenController::test_Login()
{

}

#include "test_ScreenController.moc"
