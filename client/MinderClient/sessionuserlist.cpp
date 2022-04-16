#include "sessionuserlist.h"
#include "ui_sessionuserlist.h"

SessionUserList::SessionUserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SessionUserList)
{
    ui->setupUi(this);
    qDebug() << "ul cntor";
}

SessionUserList::~SessionUserList()
{
    delete ui;
}

void SessionUserList::updateUsersList(const UsersInSessionData &data)
{
    qDebug() << "Session users list: updating data";
    this->ui->listWidgetUsersInSession->clear();
    for (int i = 0; i < data.users.count() ; ++i )
    {
        this->ui->listWidgetUsersInSession->addItem(data.users[i].nickname);
    }
}
