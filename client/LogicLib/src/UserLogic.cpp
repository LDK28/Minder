#include "UserLogic.h"

void UserLogic::addUserToSession(const ViewDataStructures::User &user) {
    HttpClientData::User convUser = convertUser(user);

    network->addUser(convUser);
}

void UserLogic::deleteUserFromSession(const ViewDataStructures::User &user) {
    HttpClientData::User convUser = convertUser(user);

    network->deleteUser(convUser);
}

void UserLogic::getUsersListInSession(const size_t sessionId) {
    HttpClientData::UsersInSessionData users = network->getUsersInSession(sessionId);

    ViewDataStructures::UsersInSessionData viewUsers = convertUsers(users);

    emit updateUsersListInSession(viewUsers);
}

HttpClientData::User UserLogic::convertUser(const ViewDataStructures::User &user) {
    return HttpClientData::User(user.nickname.toStdString());
}

ViewDataStructures::User UserLogic::reverseConvertUser(const HttpClientData::User &user) {
    return ViewDataStructures::User(QString::fromStdString(user.nickname));
}

ViewDataStructures::UsersInSessionData UserLogic::convertUsers(const HttpClientData::UsersInSessionData &usersInSession) {
    ViewDataStructures::UsersInSessionData convUsers;
    for (auto it = usersInSession.users.cbegin(); it != usersInSession.users.cend(); ++it) {
        ViewDataStructures::User user = reverseConvertUser(*it);
        convUsers.users.append(user);
    }
    return convUsers;
}

