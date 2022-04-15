#ifndef SERVER_LOGIC_HPP
#define SERVER_LOGIC_HPP

#include "ServerLogic.hpp"

class BaseLogic
{
private:
public:
    BaseLogic(/* args */){};
    ~BaseLogic(){};

    virtual void router();
};

class ServerLogic : BaseLogic
{
private:
    void prepareData();

public:
    ServerLogic(/* args */){};
    ~ServerLogic(){};

    int getConfID();
    void setConfID(int confID);
    json getDataFromDB(char &request);
    void sendDataToDB(json data);

    json router(char &request, json data);
};

#endif