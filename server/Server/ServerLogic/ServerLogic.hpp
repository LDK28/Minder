#ifndef SERVER_LOGIC_HPP
#define SERVER_LOGIC_HPP

#include "ServerLogic.hpp"

#include "DatabaseDrawDeskClient.h"
#include "DatabaseUsersClient.h"
#include "DatabaseSessionClient.h"

#include "json.hpp"

#include <set>

using json = nlohmann::json;

struct LastUpdate
{
    size_t sessionId;
    size_t userId;
};

class BaseLogic
{
private:
public:
    virtual std::string router(std::string &request) = 0;
};

class ServerLogic : BaseLogic
{
private:
    DatabaseUsersClient *DBUsersClient;
    DatabaseDrawDeskClient *DBDrawDeskClient;
    DatabaseSessionClient *DBSessionClient;

    std::set<LastUpdate> lastUpdate;

public:
    ServerLogic()
    {
        std::shared_ptr<PostgreSQLConnectParams> conParams =
            std::make_shared<PostgreSQLConnectParams>("ldk", "db_minder");

        std::shared_ptr<PostgreDatabaseClient> pg =
            std::make_shared<PostgreDatabaseClient>(conParams); // затем экземпляр postgre клиента

        DBUsersClient = new DatabaseUsersClient(pg);
        DBSessionClient = new DatabaseSessionClient(pg);
        DBDrawDeskClient = new DatabaseDrawDeskClient(pg);
        }
    ~ServerLogic()
    {
        delete DBDrawDeskClient;
        delete DBSessionClient;
        delete DBUsersClient;
    }
    std::string router(std::string &request) override;
};

#endif