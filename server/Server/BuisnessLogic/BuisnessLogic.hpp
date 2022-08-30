#ifndef BUISNESS_LOGIC_HPP
#define BUISNESS_LOGIC_HPP

#include "BuisnessLogic.hpp"

#include "DatabaseDrawDeskClient.h"
#include "DatabaseUsersClient.h"
#include "DatabaseSessionClient.h"

#include <iostream>

#include "json.hpp"

#include <set>

using json = nlohmann::json;

class IBuisnessLogic
{
public:
    virtual std::string CheckConnectionToSession(json &data) = 0;
    virtual std::string CreateSession(json &data) = 0;
    virtual std::string AddBlock(json &data) = 0;
    virtual void ChangeBlock(json &data) = 0;
    virtual void DeleteBlock(json &data) = 0;
    virtual std::string GetCurrentStateDesk(json &data) = 0;
    virtual std::string LoginUser(json &data) = 0;
    virtual std::string RegisterUser(json &data) = 0;
    virtual std::string GetUsers(json &data) = 0;
};

class BuisnessLogic : IBuisnessLogic
{
private:
    DatabaseUsersClient *DBUsersClient;
    DatabaseDrawDeskClient *DBDrawDeskClient;
    DatabaseSessionClient *DBSessionClient;

public:
    BuisnessLogic()
    {
        std::shared_ptr<PostgreSQLConnectParams> conParams =
            std::make_shared<PostgreSQLConnectParams>("ldk", "db_minder");

        std::shared_ptr<PostgreDatabaseClient> pg =
            std::make_shared<PostgreDatabaseClient>(conParams); // затем экземпляр postgre клиента

        DBUsersClient = new DatabaseUsersClient(pg);
        DBSessionClient = new DatabaseSessionClient(pg);
        DBDrawDeskClient = new DatabaseDrawDeskClient(pg);
    }
    // BuisnessLogic()
    // {
    //     std::shared_ptr<MySQLConnectParams> conParams =
    //         std::make_shared<MySQLConnectParams>("ldk", "db_minder");

    //     std::shared_ptr<MySQLDatabaseClient> pg =
    //         std::make_shared<MySQLDatabaseClient>(conParams); // затем экземпляр postgre клиента

    //     DBUsersClient = new DatabaseUsersClient(pg);
    //     DBSessionClient = new DatabaseSessionClient(pg);
    //     DBDrawDeskClient = new DatabaseDrawDeskClient(pg);
    // }
    ~BuisnessLogic()
    {
        delete DBDrawDeskClient;
        delete DBSessionClient;
        delete DBUsersClient;
    }

    std::string CheckConnectionToSession(json &data) override;
    std::string CreateSession(json &data) override;
    std::string AddBlock(json &data) override;
    void ChangeBlock(json &data) override;
    void DeleteBlock(json &data) override;
    std::string GetCurrentStateDesk(json &data) override;
    std::string LoginUser(json &data) override;
    std::string RegisterUser(json &data) override;
    std::string GetUsers(json &data) override;
};

#endif