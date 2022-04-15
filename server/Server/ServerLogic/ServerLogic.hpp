#ifndef SERVER_LOGIC_HPP
#define SERVER_LOGIC_HPP

#include "ServerLogic.hpp"
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

    virtual json router(char &request, json data) = 0;
};

class ServerLogic : BaseLogic
{
private:
    void prepareData();

public:
    ServerLogic(/* args */){};
    ~ServerLogic(){};

    int getConfID() override;
    void setConfID(int confID) override;
    json getDataFromDB(char &request) override;
    void sendDataToDB(json) override;

    json router(char &request, json) override;
};

#endif