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
        DBSessionClient.createSession(data["session"]);
    }
    if (data["title"] == "CHANGEBLOCK")
    {
        json check;
        check = DBSessionClient.checkConnectionToSession(data["connection"]["id"], data["connection"]["password"]);
        if (check["status"] == "ok")
            DBDrawDeskClient.updateBlock(data["block"]);
    }
    if (data["title"] == "DELETEBLOCK")
    {
        DBDrawDeskClient.deleteBlock(data["blockId"]);
    }
    if (data["title"] == "GETCURRENTSTATEDESK")
    {

    }
    return response;
}