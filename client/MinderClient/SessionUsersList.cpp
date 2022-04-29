#include "SessionUsersList.h"
#include "ui_SessionUsersList.h"

SessionUsersList::SessionUsersList(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SessionUsersList)
{
    ui->setupUi(this);
}

SessionUsersList::~SessionUsersList()
{
    delete ui;
}

void SessionUsersList::updateUsersList(const UsersInSessionData &data)
{
    qDebug() << "Session users list: updating data";
    this->ui->listWidgetUsersInSession->clear();
    for (int i = 0; i < data.users.count() ; ++i )
    {
        this->ui->listWidgetUsersInSession->addItem(data.users[i].nickname);
    }
}
