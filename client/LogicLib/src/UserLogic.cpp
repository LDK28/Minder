#include "UserLogic.h"

//void UserLogic::registrationUser(const ViewDataStructures::User &user) {
//    HttpClientData::RegisterData convUser = convertUser(user);

//    network->addUser(convUser);
//}

//void UserLogic::deleteUserFromSession(const ViewDataStructures::User &user) {
//    HttpClientData::User convUser = convertUser(user);

//    network->deleteUser(convUser);
//}

//void UserLogic::loginUser(const ViewDataStructures::LoginData &data) {

//}

//void UserLogic::registerUser(const ViewDataStructures::RegisterData &user) {
//    HttpClientData::RegisterData convUser = convertUser(user);

//    network->addUser(convUser);
//}

//void UserLogic::getUsersListInSession(const size_t sessionId) {
//    HttpClientData::UsersInSessionData users = network->getUsersInSession(sessionId);

//    ViewDataStructures::UsersInSessionData viewUsers = convertUsers(users);

//    emit updateUsersListInSession(viewUsers);
//}

//HttpClientData::User UserLogic::convertLoginUser(const ViewDataStructures::LoginData &user) {
//    return HttpClientData::LoginData(user.nickname.toStdString(), );
//}

//ViewDataStructures::User UserLogic::reverseConvertUser(const HttpClientData::User &user) {
//    return ViewDataStructures::User(QString::fromStdString(user.nickname));
//}

//ViewDataStructures::UsersInSessionData UserLogic::convertUsers(const HttpClientData::UsersInSessionData &usersInSession) {
//    ViewDataStructures::UsersInSessionData convUsers;
//    for (const auto &user: usersInSession.users) {
//        ViewDataStructures::User viewUser = reverseConvertUser(user);
//        convUsers.users.append(viewUser);
//    }
//    return convUsers;
//}

