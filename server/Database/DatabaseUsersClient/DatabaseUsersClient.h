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
    json createUser(json) const;
    bool checkUser(std::string name) const;
    json addUsersInSession(std::vector<int> userId, int sessionId) const;
    json getAllUsersInfo() const;
    json updateUser(json) const;
    json getUserInfo(int id) const;
    json getUserByName(std::string name) const;
    json getUsersInSession(int sessionId) const;
    json deleteUsersById(int id) const;
};
