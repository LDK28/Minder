#include "UserLogic.h"

const char *FailedLoginMsg = "Wrong password or login.";
const char *FailedRegisterMsg = "Registration failed.";

void UserLogic::loginUser(const ViewDataStructures::LoginData &user) {
    HttpClientData::LoginData convUser = convertLoginUser(user);

    auto rc = network->loginUser(convUser);

    if (rc == HttpClientData::SUCCESS) {
        emit loginUserSuccess();
    } else {
        emit loginUserFailed(FailedLoginMsg);
    }
}

void UserLogic::registerUser(const ViewDataStructures::RegisterData &user) {
    if (user.password != user.repeatPassword) {
        emit registerUserFailed(FailedRegisterMsg);
    }

    HttpClientData::RegisterData convUser = convertRegisterUser(user);

    auto rc = network->registerUser(convUser);

    if (rc == HttpClientData::SUCCESS) {
        emit loginUserSuccess();
    } else {
        emit loginUserFailed(FailedRegisterMsg);
    }
}

void UserLogic::getUsersListInSession(const size_t sessionId) {
    HttpClientData::UsersInSessionData users = network->getUsersInSession(sessionId);

    ViewDataStructures::UsersInSessionData viewUsers = convertUsers(users);

    emit updateUsersListInSession(viewUsers);
}

HttpClientData::LoginData UserLogic::convertLoginUser(const ViewDataStructures::LoginData &user) {
    return HttpClientData::LoginData(user.nickname.toStdString(), user.password.toStdString());
}

HttpClientData::RegisterData UserLogic::convertRegisterUser(const ViewDataStructures::RegisterData &user) {
    return HttpClientData::RegisterData(user.nickname.toStdString(), user.password.toStdString(), user.repeatPassword.toStdString());
}

ViewDataStructures::User UserLogic::convertUser(const HttpClientData::User &user) {
    return ViewDataStructures::User(QString::fromStdString(user.nickname));
}

ViewDataStructures::UsersInSessionData UserLogic::convertUsers(const HttpClientData::UsersInSessionData &usersInSession) {
    ViewDataStructures::UsersInSessionData convUsers;
    for (const auto &user: usersInSession.users) {
        ViewDataStructures::User viewUser = convertUser(user);
        convUsers.users.append(viewUser);
    }
    return convUsers;
}

