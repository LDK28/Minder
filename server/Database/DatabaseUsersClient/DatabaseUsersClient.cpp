#include "DatabaseUsersClient.h"

json DatabaseUsersClient::createUser(json) { return json{{}}; }
bool DatabaseUsersClient::checkUser(json) { return true; }
json DatabaseUsersClient::getAllUsersInfo() { return json{{}}; }
json DatabaseUsersClient::getUserInfo(int id) { return json{{}}; }
json DatabaseUsersClient::selectUsersByName(std::string name) {
    return json{{}};
}
json DatabaseUsersClient::deleteUsersById(int id) { return json{{}}; }