#include "logiccontroller.h"

LogicController::LogicController(QObject *parent)
    : QObject{parent}
{
        connect(&screenController, &ScreenController::validateLoginData, this, &LogicController::validateLoginData);
        connect(this, &LogicController::validationLoginDataSuccess, &screenController, &ScreenController::validationLoginDataSuccess);

        connect(&screenController, &ScreenController::validateRegisterData, this, &LogicController::validateRegisterData);
        connect(this, &LogicController::validationRegisterDataSuccess, &screenController, &ScreenController::validationRegisterDataSuccess);

        connect(&screenController, &ScreenController::saveSettings, this, &LogicController::saveSettings);
        connect(this, &LogicController::savingSettingsSuccess, &screenController, &ScreenController::savingSettingsSuccess);

        connect(&screenController, &ScreenController::createNewSession, this, &LogicController::validateSessionCreationData);
        connect(this, &LogicController::sessionCreationSuccess, &screenController, &ScreenController::creationNewSessionSuccess);

        connect(&screenController, &ScreenController::connectToSession, this, &LogicController::validateSessionConnectionData);
        connect(this, &LogicController::sessionConnectionSuccess, &screenController, &ScreenController::connectionToSessionSuccess);

        connect(&screenController, &ScreenController::getUsersInSession, this, &LogicController::requestUpdateUsersListInSession);
        connect(this, &LogicController::updateUsersListInSession, &screenController, &ScreenController::receiveUsersListInSession);
}

void LogicController::validateLoginData(LoginData data)
{
    qDebug() << "Logic controller: validation login data test(success): " << data.nickname << " " << data.password;
    emit validationLoginDataSuccess();
}
void LogicController::validateRegisterData(RegisterData data)
{
    qDebug() << "Logic controller: validation register data test(success): " << data.nickname << " " << data.password << " " << data.repeatPassword;
    emit validationRegisterDataSuccess();
}
void LogicController::saveSettings(SettingsData data)
{
    qDebug() << "Logic controller: saving settings test(success): " << data.serverIP << " " << data.serverPort;
    emit savingSettingsSuccess();
}
void LogicController::validateSessionCreationData(SessionCreationData data)
{
    qDebug() << "Logic controller: session creation test(success): " << data.sessionName << " " << data.sessionPassword << " " << data.sessionRepeatPassword;
    emit sessionCreationSuccess();
}
void LogicController::validateSessionConnectionData(SessionConnectionData data)
{
    qDebug() << "Logic controller: session connection test(success): " << data.sessionID << " " << data.sessionPassword;
    emit sessionConnectionSuccess();
}

void LogicController::requestUpdateUsersListInSession()
{
    QList<User> ulist;
    ulist.append(User("Us 1"));
    ulist.append(User("Us 2"));

    UsersInSessionData data = {ulist};

    emit updateUsersListInSession(data);
}
