#include "UserLogic.h"

const char *LOGIN_ERROR_MSG = "Wrong password or login.";
const char *REGISTER_ERROR_MSG = "Registration failed.";

void UserLogic::loginUser(const ViewDataStructures::LoginData &user) {
    HttpClientData::LoginData convUser = convertLoginUser(user);

    size_t id = network->loginUser(convUser);

    if (id > 0) {
        userId = id;
        emit loginUserSuccess();
    } else {
        emit loginUserFailed(LOGIN_ERROR_MSG);
    }
}

void UserLogic::registerUser(const ViewDataStructures::RegisterData &user) {
    if (user.password != user.repeatPassword) {
        emit registerUserFailed(REGISTER_ERROR_MSG);
        return;
    }

    HttpClientData::RegisterData convUser = convertRegisterUser(user);

    size_t id = network->registerUser(convUser);

    if (id > 0) {
        userId = id;
        emit registerUserSuccess();
    } else {
        emit registerUserFailed(REGISTER_ERROR_MSG);
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

