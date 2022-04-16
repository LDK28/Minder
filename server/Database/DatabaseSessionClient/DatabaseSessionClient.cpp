#include "DatabaseSessionClient.h"

json DatabaseSessionClient::createSession() { return json{{}}; }
json DatabaseSessionClient::addUsersInSession(json) { return json{{}}; }
bool DatabaseSessionClient::checkSession(int id) { return true; }
json DatabaseSessionClient::updateSession(json) { return json{{}}; }
json DatabaseSessionClient::getSessionInfo(int id) { return json{{}}; }
json DatabaseSessionClient::selectSessionsWithUser(int userId) {
    return json{{}};
}
json DatabaseSessionClient::deleteSession(int id) { return json{{}}; }