#include "LogicController.h"

const char *regIP = "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";

const char *regNum = "(\\d*)";

void LogicController::connectView() {
    connect(screenController.get(), &ScreenController::transmitSettings, this, &LogicController::changeSettings);
    connect(this, &LogicController::changeSettingsSuccess, screenController.get(), &ScreenController::savingSettingsSuccess);
    connect(this, &LogicController::changeSettingsFailed, screenController.get(), &ScreenController::savingSettingsFailed);

    connect(screenController.get(), &ScreenController::transmitCreationNewSession, this, &LogicController::createNewSession);
    connect(this, &LogicController::sessionCreationSuccess, screenController.get(), &ScreenController::creationNewSessionSuccess);
    connect(this, &LogicController::sessionCreationFailed, screenController.get(), &ScreenController::creationNewSessionFailed);

    connect(screenController.get(), &ScreenController::transmitConnectionToSession, this, &LogicController::connectToSession);
    connect(this, &LogicController::sessionConnectionSuccess, screenController.get(), &ScreenController::connectionToSessionSuccess);
    connect(this, &LogicController::sessionConnectionFailed, screenController.get(), &ScreenController::connectionToSessionFailed);

//    connect(screenController.get(), &ScreenController::getUsersInSessionData, this, &LogicController::getUsersListInSession);
//    connect(this, &LogicController::updateUsersListInSession, screenController.get(), &ScreenController::receiveUsersListInSession);

    connect(screenController.get(), &ScreenController::sendNewBlock, &drawing, &DrawingLogic::sendNewBlock);
    connect(&drawing, &DrawingLogic::sendNewBlockIdToSession, screenController.get(), &ScreenController::receiveNewBlockId);

    connect(screenController.get(), &ScreenController::getMindMapInSessionData, &drawing, &DrawingLogic::getMindMapInSession);
    connect(&drawing, &DrawingLogic::updateMindMapDataInSession, screenController.get(), &ScreenController::receiveMindMapDataInSession);

    connect(screenController.get(), &ScreenController::sessionClosed, this, &LogicController::disconnectSession);
}

void LogicController::disconnectView() {
    disconnect(screenController.get(), &ScreenController::transmitSettings, this, &LogicController::changeSettings);
    disconnect(this, &LogicController::changeSettingsSuccess, screenController.get(), &ScreenController::savingSettingsSuccess);
    disconnect(this, &LogicController::changeSettingsFailed, screenController.get(), &ScreenController::savingSettingsFailed);

    disconnect(screenController.get(), &ScreenController::transmitCreationNewSession, this, &LogicController::createNewSession);
    disconnect(this, &LogicController::sessionCreationSuccess, screenController.get(), &ScreenController::creationNewSessionSuccess);
    disconnect(this, &LogicController::sessionCreationFailed, screenController.get(), &ScreenController::creationNewSessionFailed);

    disconnect(screenController.get(), &ScreenController::transmitConnectionToSession, this, &LogicController::connectToSession);
    disconnect(this, &LogicController::sessionConnectionSuccess, screenController.get(), &ScreenController::connectionToSessionSuccess);
    disconnect(this, &LogicController::sessionConnectionFailed, screenController.get(), &ScreenController::connectionToSessionFailed);

//    disconnect(screenController.get(), &ScreenController::getUsersInSessionData, this, &LogicController::getUsersListInSession);
//    disconnect(this, &LogicController::updateUsersListInSession, screenController.get(), &ScreenController::receiveUsersListInSession);

    disconnect(screenController.get(), &ScreenController::sendNewBlock, &drawing, &DrawingLogic::sendNewBlock);
    disconnect(&drawing, &DrawingLogic::sendNewBlockIdToSession, screenController.get(), &ScreenController::receiveNewBlockId);

    disconnect(screenController.get(), &ScreenController::getMindMapInSessionData, &drawing, &DrawingLogic::getMindMapInSession);
    disconnect(&drawing, &DrawingLogic::updateMindMapDataInSession, screenController.get(), &ScreenController::receiveMindMapDataInSession);

    disconnect(screenController.get(), &ScreenController::sessionClosed, this, &LogicController::disconnectSession);
}

void LogicController::changeSettings(const SettingsData &settings) {
    if (!settings.serverPort.contains(regNum) || settings.serverIP.contains(regIP)) {
        emit sessionConnectionFailed();
        return;
    }

    Settings convSettings = convertSettings(settings);
    returnCode rc = network->updateSettings(convSettings);

    if (rc == SUCCESS) {
        emit changeSettingsSuccess();
    } else {
        emit changeSettingsFailed();
    }
}

void LogicController::createNewSession(const SessionCreationData &session) {
    if (session.password != session.repeatPassword) {
        emit sessionCreationFailed();
        return;
    }

    NewSession convSession = convertNewSession(session);
    size_t sessionId = network->createSession(convSession);

    if (sessionId == 0) {
        emit sessionCreationFailed();
    } else {
        emit sessionCreationSuccess(SessionData(sessionId, session.name));
    }
}

void LogicController::connectToSession(const SessionConnectionData &session) {
    if (!session.id.contains(regNum)) {
        emit sessionConnectionFailed();
        return;
    }

    ExistSession convSession = convertExistSession(session);
    std::string sessionName = network->checkConnectionToSession(convSession);

    if (sessionName.empty()) {
        emit sessionConnectionFailed();
    } else {
        emit sessionConnectionSuccess(SessionData(session.id.toInt(), QString::fromStdString(sessionName)));
    }
}

//void LogicController::getUsersListInSession() {
//    QList<User> ulist;
//    srand(time(NULL));
//    for(int i = 0; i < 1 + rand() % (10 - 1); ++i)
//    {
//        ulist.append(QString("Test User ") + QString::number(i + 1));
//    }
//    UsersInSessionData data = {ulist};

//    emit updateUsersListInSession(data);
//}

void LogicController::disconnectSession() {
    network->disconnect();
}

Settings LogicController::convertSettings(const SettingsData &settings) {
    return Settings(settings.serverIP.toStdString(), settings.serverPort.toStdString());
}

NewSession LogicController::convertNewSession(const SessionCreationData &session) {
    return NewSession(session.name.toStdString(), session.password.toStdString());
}

ExistSession LogicController::convertExistSession(const SessionConnectionData &session) {
    return ExistSession(session.id.toInt(), session.password.toStdString());
}

