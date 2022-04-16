#ifndef USER_H
#define USER_H

#include <QtWidgets>

#include "DataStructures.h"
#include "HttpClient.h"

class User : public QObject {
Q_OBJECT
public:
    explicit User() = default;
    explicit User(HttpClient *network_) : network(network_) {}
    ~User() = default;
public slots:
    void deleteUser();
    void getUsers(Users &users);
signals:
    void sendUsers();
private:
    std::shared_ptr <HttpClient> network = nullptr;
};

#endif // USER_H
