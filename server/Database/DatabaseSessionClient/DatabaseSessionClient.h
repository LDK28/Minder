#pragma once
#include <vector>

#include "DatabaseClient.h"
#include <memory>

class DatabaseSessionClient {
 private:
    std::shared_ptr<DatabaseClient> client;

 public:
    DatabaseSessionClient(std::shared_ptr<DatabaseClient> cl);

    json createSession(json data) const;
    bool checkSession(std::string name) const;
    json updateSession(json) const;
    json getSessionInfo(int id) const;
    json deleteSession(int id) const;
};
