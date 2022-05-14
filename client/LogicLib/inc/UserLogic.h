#ifndef USER_H
#define USER_H

#include <QtWidgets>

#include "DataStructures.h"
#include "HttpClient.h"

class UserLogic : public QObject {
Q_OBJECT
public:
    explicit UserLogic() = default;
    explicit UserLogic(HttpClient *network_) : network(network_) {}
    ~UserLogic() = default;
public slots:
    //void deleteUser();
    //void getUsers(Users &users);
    //updateUsersListInSession
signals:
    void sendUsers();
private:
    HttpClient *network = nullptr;
};

#endif // USER_H
