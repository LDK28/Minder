#ifndef SESSIONUSERSLIST_H
#define SESSIONUSERSLIST_H

#include <QFrame>

#include "DataStructures.h"

using namespace ViewDataStructures;

namespace Ui {
class SessionUserList;
}

class SessionUserList : public QFrame
{
    Q_OBJECT

public:
    explicit SessionUserList(QWidget *parent = nullptr);
    ~SessionUserList();

    void updateUsersList(const UsersInSessionData &data);

private:
    Ui::SessionUserList *ui;
};

#endif // SESSIONUSERSLIST_H
