#include <QObject>
#include <QTest>

#include "SessionUsersList.h"
#include "DataStructures.h"

namespace Ui {
class SessionUsersList;
}

class test_SessionUsersList : public QObject
{
    Q_OBJECT
public:
    explicit test_SessionUsersList(QObject *parent = 0) : QObject(parent) {}

private slots: // должны быть приватными
    void test_updateUsersList();
};


void test_SessionUsersList::test_updateUsersList()
{

    SessionUsersList sul;
    UsersInSessionData data;
    data.users.append(User("1"));
    sul.updateUsersList(data);
    QCOMPARE(1,1);
}

#include "test_SessionUsersList.moc"
