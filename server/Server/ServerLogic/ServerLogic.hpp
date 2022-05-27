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
    BaseLogic(/* args */){};
    ~BaseLogic(){};

    virtual int getConfID() = 0;
    virtual void setConfID(int confID) = 0;
    virtual json getDataFromDB(char &request) = 0;
    virtual void sendDataToDB(json data) = 0;

    virtual std::string router(std::string &request) = 0;
};

class ServerLogic : BaseLogic
{
private:
    void prepareData();
    
    DatabaseUsersClient DBUsersClient;
    DatabaseDrawDeskClient DBDrawDeskClient;
    DatabaseSessionClient DBSessionClient;

    json ActiveUsers;
public:
    ServerLogic(/* args */){};
    ~ServerLogic(){};

    int getConfID() override;
    void setConfID(int confID) override;
    json getDataFromDB(char &request) override;
    void sendDataToDB(json) override;

    std::string router(std::string &request) override;
};

#endif