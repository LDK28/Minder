#include "ServerLogic.hpp"

std::string ServerLogic::router(std::string &request)
{
    std::string response = "";
    json data = json::parse(request);

    if (data["title"] == "CHECKCONNECTIONTOSESSION")
        response = buisnessLogic.CheckConnectionToSession(data);
    if (data["title"] == "CREATESESSION")
        response = buisnessLogic.CreateSession(data);
    if (data["title"] == "ADDBLOCK")
        response = buisnessLogic.AddBlock(data);
    if (data["title"] == "CHANGEBLOCK")
        buisnessLogic.ChangeBlock(data);
    if (data["title"] == "DELETEBLOCK")
        buisnessLogic.DeleteBlock(data);
    if (data["title"] == "GETCURRENTSTATEDESK")
        response = buisnessLogic.GetCurrentStateDesk(data);
    if (data["title"] == "GETUSERS")
        response = buisnessLogic.GetUsers(data);
    if (data["title"] == "LOGINUSER")
        response = buisnessLogic.LoginUser(data);
    if (data["title"] == "REGISTERUSER")
        response = buisnessLogic.RegisterUser(data);
    if (data["title"] == "PING")
    {
        size_t sessionId = data["sessionId"];
        size_t userId = data["userId"];
        // for (auto &elem : this->lastUpdate)
        //     if (1);
    }

    return response;
}
