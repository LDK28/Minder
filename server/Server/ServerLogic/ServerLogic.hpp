#ifndef SERVER_LOGIC_HPP
#define SERVER_LOGIC_HPP

#include "ServerLogic.hpp"

#include "DatabaseDrawDeskClient.h"
#include "DatabaseUsersClient.h"
#include "DatabaseSessionClient.h"

#include "json.hpp"

using json = nlohmann::json;

class BaseLogic
{
private:
public:
    virtual std::string router(std::string &request) = 0;
};

class ServerLogic : BaseLogic
{
private:
    void prepareData();

    DatabaseUsersClient DBUsersClient;
    DatabaseDrawDeskClient DBDrawDeskClient;
    DatabaseSessionClient DBSessionClient;

public:
    ServerLogic();
    ~ServerLogic(){};

    std::string router(std::string &request) override;
};

#endif