#include "DatabaseSessionClient.h"

json DatabaseSessionClient::createSession(json) {}
json DatabaseSessionClient::addUsersInSession(json) {}
bool DatabaseSessionClient::checkSession(int id) {}
json DatabaseSessionClient::getSessionInfo(int id) {}
std::vector<int> DatabaseSessionClient::selectSessionsWithUser(int userId) {}
json DatabaseSessionClient::deleteSession(int id) {}