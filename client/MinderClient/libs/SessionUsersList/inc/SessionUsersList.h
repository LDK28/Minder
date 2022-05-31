#ifndef SESSIONUSERSLIST_H
#define SESSIONUSERSLIST_H

#include <QFrame>

#include "ViewDataStructures.h"

namespace Ui {
class SessionUsersList;
}

class SessionUsersList : public QFrame
{
    Q_OBJECT

public:
    explicit SessionUsersList(QWidget *parent = nullptr);
    ~SessionUsersList();

    void updateUsersList(const ViewDataStructures::UsersInSessionData &data);

private:
    Ui::SessionUsersList *ui;

    friend class test_SessionUsersList;
};

#endif // SESSIONUSERSLIST_H
