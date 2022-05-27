#include <QObject>
#include <QTest>

#include "SessionUsersList.h"
#include "ViewDataStructures.h"

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
    ViewDataStructures::UsersInSessionData data;
    data.users.append(ViewDataStructures::User("1"));
    sul.updateUsersList(data);
    QCOMPARE(1,1);
}

#include "test_SessionUsersList.moc"
