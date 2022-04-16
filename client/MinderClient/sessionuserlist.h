#ifndef SESSIONUSERLIST_H
#define SESSIONUSERLIST_H

#include <QWidget>
#include "datastructures.h"

namespace Ui {
class SessionUserList;
}

class SessionUserList : public QWidget
{
    Q_OBJECT

public:
    explicit SessionUserList(QWidget *parent = nullptr);
    ~SessionUserList();

    void updateUsersList(const UsersInSessionData &data);

private:
    Ui::SessionUserList *ui;
};

#endif // SESSIONUSERLIST_H
