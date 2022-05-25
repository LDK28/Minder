#include "ServerLogic.hpp"

int ServerLogic::getConfID() {}
void ServerLogic::setConfID(int confID) {}
json ServerLogic::getDataFromDB(char &request) {}
void ServerLogic::sendDataToDB(json) {}

std::string ServerLogic::router(std::string &request)
{
    std::string response;
    json data = json::parse(request);
    if (data["title"] == "GETUSERS")
        response = this->ActiveUsers.dump();
    if (data["title"] == "CHECKCONNECTIONTOSESSION")
    {
    }
    if (data["title"] == "CREATESESSION")
    {
    }
    if (data["title"] == "DELETEBLOCK")
    {
    }
    if (data["title"] == "GETCURRENTSTATEDESK")
    {
    }
}