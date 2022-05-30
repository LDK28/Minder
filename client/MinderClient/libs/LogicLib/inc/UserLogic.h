#ifndef USER_H
#define USER_H

#include <QtWidgets>

#include "HttpDataStructures.h"
#include "ViewDataStructures.h"
#include "HttpClient.hpp"

class UserLogic : public QObject {
Q_OBJECT
public:
    explicit UserLogic() = default;
    explicit UserLogic(HttpClient *network_, QTimer* timer_) : network(network_), timer(timer_) {}
    ~UserLogic() = default;

    size_t getUser() { return userId; }
public slots:
    void getUsersListInSession(const size_t sessionId);
    void loginUser(const ViewDataStructures::LoginData &user);
    void registerUser(const ViewDataStructures::RegisterData &user);
signals:
    void updateUsersListInSession(const ViewDataStructures::UsersInSessionData &);
    void loginUserSuccess();
    void loginUserFailed(const QString &);
    void registerUserSuccess();
    void registerUserFailed(const QString &);
    void block();
    void unblock();
private:
    HttpClient *network = nullptr;
    QTimer *timer = nullptr;
    size_t userId = 0;

    HttpClientData::UserData convertLoginUser(const ViewDataStructures::LoginData &user);
    HttpClientData::UserData convertRegisterUser(const ViewDataStructures::RegisterData &user);
    ViewDataStructures::User convertUser(const HttpClientData::User &user);
    ViewDataStructures::UsersInSessionData convertUsers(const HttpClientData::UsersInSessionData &usersInSession);
};

#endif // USER_H
