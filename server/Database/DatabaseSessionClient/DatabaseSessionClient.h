#pragma once
#include <memory>
#include <vector>

#include "DatabaseClient.h"

class DatabaseSessionClient {
 private:
    std::shared_ptr<DatabaseClient> client;

 public:
    DatabaseSessionClient(std::shared_ptr<DatabaseClient> cl);

    json createSession(const json &data) const;
    bool checkSession(const std::string &name) const;
    json updateSession(const json &) const;
    json getSessionInfo(int id) const;
    json deleteSession(int id) const;
    json checkConnectionToSession(int id, const std::string &password);
};
