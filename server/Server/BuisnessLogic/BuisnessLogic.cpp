#include "BuisnessLogic.hpp"

std::string BuisnessLogic::CheckConnectionToSession(json &data)
{
    int id = data["session"]["id"];
    std::string password = data["session"]["password"];
    json dbResponse = DBSessionClient->checkConnectionToSession(id, password);
    if (dbResponse["status"] == "ok")
    {
        std::string id = dbResponse["sessions"]["id"];
        int sessionId = std::stoi(id, nullptr, 10);
        std::vector<int> userId;
        userId.push_back(data["userId"]);
        DBUsersClient->addUsersInSession(userId, sessionId);

        return dbResponse["sessions"]["name"];
    }

    return std::string("");
}

std::string BuisnessLogic::CreateSession(json &data)
{
    json session = DBSessionClient->createSession(data["session"]);
    std::vector<int> userId;
    userId.push_back(data["userId"]);
    std::string sessionId = session["id"];
    json dbresponse = DBUsersClient->addUsersInSession(userId, std::stoi(sessionId));
    return dbresponse["id"];
}

std::string BuisnessLogic::AddBlock(json &data)
{
    int deskId = data["deskId"];
    json block = data["block"];
    block["desk_id"] = deskId;
    block.erase("id");
    json dbResponse = DBDrawDeskClient->addBlock(deskId, block);
    return dbResponse["id"];
}

void BuisnessLogic::ChangeBlock(json &data)
{
    DBDrawDeskClient->updateBlock(data["block"]);
}

void BuisnessLogic::DeleteBlock(json &data)
{
    int blockId = data["blockId"];
    DBDrawDeskClient->deleteBlock(blockId);
}
std::string BuisnessLogic::GetCurrentStateDesk(json &data)
{
    int deskId = data["sessionId"];
    json blocks = DBDrawDeskClient->getBlocksInfoFromDesk(deskId);
    return blocks.dump();
}
std::string BuisnessLogic::LoginUser(json &data)
{
    std::string name = data["user"]["nickname"];
    std::string password = data["user"]["password"];

    bool check = DBUsersClient->validateUser(name, password);
    if (check == true)
    {
        json user = DBUsersClient->getUserByName(name);
        int id = user["users"][0]["id"];
        return std::to_string(id);
    }
    else
        return "0";
}
std::string BuisnessLogic::RegisterUser(json &data)
{
    json dbRespose = DBUsersClient->createUser(data["user"]);
    return dbRespose["id"];
}
std::string BuisnessLogic::GetUsers(json &data)
{
    int sessionId = data["sessionId"];
    json dbResponse = DBUsersClient->getUsersInSession(sessionId);
    return dbResponse.dump();
}