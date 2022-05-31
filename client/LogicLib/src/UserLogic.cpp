#include "UserLogic.h"

const char *LOGIN_ERROR_MSG = "Wrong password or login.";
const char *REGISTER_ERROR_MSG = "Registration failed.";

void UserLogic::loginUser(const ViewDataStructures::LoginData &user) {
    emit block();

    HttpClientData::UserData convUser = convertLoginUser(user);

    timer->stop();
    size_t id = network->loginUser(convUser);
    timer->start();

    emit unblock();
    if (id > 0) {
        userId = id;
        emit loginUserSuccess();
    } else {
        emit loginUserFailed(LOGIN_ERROR_MSG);
    }
}

void UserLogic::registerUser(const ViewDataStructures::RegisterData &user) {
    emit block();
    if (user.password != user.repeatPassword) {
        emit registerUserFailed(REGISTER_ERROR_MSG);
        return;
    }

    HttpClientData::UserData convUser = convertRegisterUser(user);

    timer->stop();
    size_t id = network->registerUser(convUser);
    timer->start();

    emit unblock();
    if (id > 0) {
        userId = id;
        emit registerUserSuccess();
    } else {
        emit registerUserFailed(REGISTER_ERROR_MSG);
    }
}

void UserLogic::getUsersListInSession(const size_t sessionId) {
    emit block();
    timer->stop();
    HttpClientData::UsersInSessionData users = network->getUsersInSession(sessionId);
    timer->start();

    ViewDataStructures::UsersInSessionData viewUsers = convertUsers(users);

    emit unblock();
    emit updateUsersListInSession(viewUsers);
}

HttpClientData::UserData UserLogic::convertLoginUser(const ViewDataStructures::LoginData &user) {
    return HttpClientData::UserData(user.nickname.toStdString(), user.password.toStdString());
}

HttpClientData::UserData UserLogic::convertRegisterUser(const ViewDataStructures::RegisterData &user) {
    return HttpClientData::UserData(user.nickname.toStdString(), user.password.toStdString());
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

