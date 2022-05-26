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
    void deleteUserFromSession(const ViewDataStructures::User &user);
    void addUserToSession(const ViewDataStructures::User &user);
    void getUsersListInSession(const size_t sessionId);
signals:
    void updateUsersListInSession(const ViewDataStructures::UsersInSessionData &);
private:
    HttpClient *network = nullptr;

    HttpClientData::User convertUser(const ViewDataStructures::User &user);
    ViewDataStructures::User reverseConvertUser(const HttpClientData::User &user);
    ViewDataStructures::UsersInSessionData convertUsers(const HttpClientData::UsersInSessionData &usersInSession);
};

#endif // USER_H
