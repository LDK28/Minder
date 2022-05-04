#ifndef USER_H
#define USER_H

#include <QtWidgets>

#include "DataStructures.h"
#include "HttpClient.h"

class UserLogic : public QObject {
Q_OBJECT
public:
    explicit UserLogic() = default;
    explicit UserLogic(std::shared_ptr<HttpClient> network_) : network(network_) {}
    explicit UserLogic(HttpClient *network_) : network(network_) {}
    ~UserLogic() = default;
public slots:
    //void deleteUser();
    //void getUsers(Users &users);
signals:
    //void sendUsers();
private:
    std::shared_ptr <HttpClient> network = nullptr;
};

#endif // USER_H
