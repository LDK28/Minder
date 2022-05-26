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
    void loginUser(const ViewDataStructures::LoginData &user);
    void registerUser(const ViewDataStructures::RegisterData &user);
signals:
    void updateUsersListInSession(const ViewDataStructures::UsersInSessionData &);
    void loginUserSuccess();
    void loginUserFailed(const QString &);
    void registerUserSuccess();
    void registerUserFailed(const QString &);
private:
    HttpClient *network = nullptr;

    HttpClientData::LoginData convertLoginUser(const ViewDataStructures::LoginData &user);
    HttpClientData::RegisterData convertRegisterUser(const ViewDataStructures::RegisterData &user);
    ViewDataStructures::User convertUser(const HttpClientData::User &user);
    ViewDataStructures::UsersInSessionData convertUsers(const HttpClientData::UsersInSessionData &usersInSession);
};

#endif // USER_H
