#pragma once

#include <map>
#include <string>

#include "DatabaseClient.h"
#include "PostgreDatabaseClient.h"

class DatabaseUsersClient {
 private:
    std::shared_ptr<DatabaseClient> client;

 public:
    DatabaseUsersClient() = default;
    DatabaseUsersClient(std::shared_ptr<DatabaseClient> client);
    json createUser(const json &) const;
    bool checkUser(const std::string &name) const;
    bool validateUser(const std::string &name,
                      const std::string &password) const;
    json addUsersInSession(const std::vector<int> &userId, int sessionId) const;
    json deleteUserFromSession(const int &userId) const;
    json getAllUsersInfo() const;
    json updateUser(const json &) const;
    json getUserInfo(int id) const;
    json getUserByName(const std::string &name) const;
    json getUsersInSession(int sessionId) const;
    json deleteUsersById(int id) const;
};
