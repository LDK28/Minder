#include "ServerLogic.hpp"

std::string ServerLogic::router(std::string &request)
{
    std::string response = "";
    json data = json::parse(request);

    if (data["title"] == "CHECKCONNECTIONTOSESSION")
    {
        int id = data["session"]["id"];
        std::string password = data["session"]["password"];
        json dbResponse = DBSessionClient.checkConnectionToSession(id, password);
        if (dbResponse["status"] == "ok")
        {
            std::string id = dbResponse["sessions"]["id"];
            int sessionId = std::stoi(id, nullptr, 10);
            std::vector<int> userId;
            userId.push_back(data["userId"]);
            DBUsersClient.addUsersInSession(userId, sessionId);

            response = dbResponse["sessions"]["name"];
        }
    }
    if (data["title"] == "CREATESESSION")
    {
        DBSessionClient.createSession(data["session"]);
        json session = DBSessionClient.getSessionInfo(data["session"]);
        std::vector<int> userId;
        userId.push_back(data["userId"]);
        std::string sessionId = session["id"];
        json dbresponse = DBUsersClient.addUsersInSession(userId, std::stoi(sessionId));
        response = dbresponse["id"];
    }
    if (data["title"] == "ADDBLOCK")
    {
        int deskId = data["deskId"];
        json block = data["block"];
        block["desk_id"] = deskId;
        block.erase("id");
        json dbResponse = DBDrawDeskClient.addBlock(deskId, block);
        response = dbResponse["id"];
    }
    if (data["title"] == "CHANGEBLOCK")
    {
        DBDrawDeskClient.updateBlock(data["block"]);
    }

    if (data["title"] == "DELETEBLOCK")
    {
        int blockId = data["blockId"];
        DBDrawDeskClient.deleteBlock(blockId);
    }
    if (data["title"] == "GETCURRENTSTATEDESK")
    {
        int deskId = data["sessionId"];
        json blocks = DBDrawDeskClient.getBlocksInfoFromDesk(deskId);
        response = blocks.dump();
    }
    if (data["title"] == "GETUSERS")
    {
        int sessionId = data["sessionId"];
        json dbResponse = DBUsersClient.getUsersInSession(sessionId);
        response = dbResponse.dump();

    }
    if (data["title"] == "LOGINUSER")
    {
        std::string name = data["user"]["nickname"];
        std::string password = data["user"]["password"];

        bool check = DBUsersClient.validateUser(name, password);
        if (check == true)
        {
            json user = DBUsersClient.getUserByName(name);
            int id = user["users"][0]["id"];
            response = std::to_string(id);
        }
    }
    if (data["title"] == "REGISTERUSER")
    {
        json dbRespose = DBUsersClient.createUser(data["user"]);
        response = dbRespose["id"];
    }

    return response;
}