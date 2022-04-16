#include "DatabaseSessionClient.h"

json DatabaseSessionClient::createSession(json) { return json{{}}; }
json DatabaseSessionClient::addUsersInSession(json) { return json{{}}; }
bool DatabaseSessionClient::checkSession(int id) { return true; }
json DatabaseSessionClient::getSessionInfo(int id) { return json{{}}; }
std::vector<int> DatabaseSessionClient::selectSessionsWithUser(int userId) {
    return json{{}};
}
json DatabaseSessionClient::deleteSession(int id) { return json{{}}; }