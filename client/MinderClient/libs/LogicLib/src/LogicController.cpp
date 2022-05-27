#include "LogicController.h"

const char *REG_IP = "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                    "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";

const char *REG_NUM = "\\d";

const char *SETTINGS_ERROR_MSG = "Settings change failed.";
const char *NEW_SESSION_ERROR_MSG = "Session creation failed.";
const char *EXIST_SESSION_ERROR_MSG = "Session connection failed.";

void LogicController::connectView() {
    connect(&screenController, &ScreenController::transmitLoginData, &user, &UserLogic::loginUser);
    connect(&user, &UserLogic::loginUserSuccess, &screenController, &ScreenController::validationLoginDataSuccess);
    connect(&user, &UserLogic::loginUserFailed, &screenController, &ScreenController::validationLoginDataFailed);

    connect(&screenController, &ScreenController::transmitRegisterData, &user, &UserLogic::registerUser);
    connect(&user, &UserLogic::registerUserSuccess, &screenController, &ScreenController::validationRegisterDataSuccess);
    connect(&user, &UserLogic::registerUserFailed, &screenController, &ScreenController::validationRegisterDataFailed);

    connect(&screenController, &ScreenController::transmitSettings, this, &LogicController::changeSettings);
    connect(this, &LogicController::changeSettingsSuccess, &screenController, &ScreenController::savingSettingsSuccess);
    connect(this, &LogicController::changeSettingsFailed, &screenController, &ScreenController::savingSettingsFailed);

    connect(&screenController, &ScreenController::transmitCreationNewSession, this, &LogicController::createNewSession);
    connect(this, &LogicController::sessionCreationSuccess, &screenController, &ScreenController::creationNewSessionSuccess);
    connect(this, &LogicController::sessionCreationFailed, &screenController, &ScreenController::creationNewSessionFailed);

    connect(&screenController, &ScreenController::transmitConnectionToSession, this, &LogicController::connectToSession);
    connect(this, &LogicController::sessionConnectionSuccess, &screenController, &ScreenController::connectionToSessionSuccess);
    connect(this, &LogicController::sessionConnectionFailed, &screenController, &ScreenController::connectionToSessionFailed);

    connect(&screenController, &ScreenController::getUsersInSessionData, &user, &UserLogic::getUsersListInSession);
    connect(&user, &UserLogic::updateUsersListInSession, &screenController, &ScreenController::receiveUsersListInSession);

    connect(&screenController, &ScreenController::sendNewBlock, &drawing, &DrawingLogic::sendNewBlock);
    connect(&drawing, &DrawingLogic::sendNewBlockIdToSession, &screenController, &ScreenController::receiveNewBlockId);

    connect(&screenController, &ScreenController::getMindMapInSessionData, &drawing, &DrawingLogic::getMindMapInSession);
    connect(&drawing, &DrawingLogic::updateMindMapDataInSession, &screenController, &ScreenController::receiveMindMapDataInSession);

    connect(&drawing, &DrawingLogic::addNewBlock, &screenController, &ScreenController::receiveBlock);
    connect(&drawing, &DrawingLogic::deleteBlock, &screenController, &ScreenController::receiveDeltedBlockId);

    connect(&screenController, &ScreenController::sessionClosed, this, &LogicController::disconnectSession);
}

void LogicController::disconnectView() {
    disconnect(&screenController, &ScreenController::transmitLoginData, &user, &UserLogic::loginUser);
    disconnect(&user, &UserLogic::loginUserSuccess, &screenController, &ScreenController::validationLoginDataSuccess);
    disconnect(&user, &UserLogic::loginUserFailed, &screenController, &ScreenController::validationLoginDataFailed);

    disconnect(&screenController, &ScreenController::transmitRegisterData, &user, &UserLogic::registerUser);
    disconnect(&user, &UserLogic::registerUserSuccess, &screenController, &ScreenController::validationRegisterDataSuccess);
    disconnect(&user, &UserLogic::registerUserFailed, &screenController, &ScreenController::validationRegisterDataFailed);

    disconnect(&screenController, &ScreenController::transmitSettings, this, &LogicController::changeSettings);
    disconnect(this, &LogicController::changeSettingsSuccess, &screenController, &ScreenController::savingSettingsSuccess);
    disconnect(this, &LogicController::changeSettingsFailed, &screenController, &ScreenController::savingSettingsFailed);

    disconnect(&screenController, &ScreenController::transmitCreationNewSession, this, &LogicController::createNewSession);
    disconnect(this, &LogicController::sessionCreationSuccess, &screenController, &ScreenController::creationNewSessionSuccess);
    disconnect(this, &LogicController::sessionCreationFailed, &screenController, &ScreenController::creationNewSessionFailed);

    disconnect(&screenController, &ScreenController::transmitConnectionToSession, this, &LogicController::connectToSession);
    disconnect(this, &LogicController::sessionConnectionSuccess, &screenController, &ScreenController::connectionToSessionSuccess);
    disconnect(this, &LogicController::sessionConnectionFailed, &screenController, &ScreenController::connectionToSessionFailed);

    disconnect(&screenController, &ScreenController::getUsersInSessionData, &user, &UserLogic::getUsersListInSession);
    disconnect(&user, &UserLogic::updateUsersListInSession, &screenController, &ScreenController::receiveUsersListInSession);

    disconnect(&screenController, &ScreenController::sendNewBlock, &drawing, &DrawingLogic::sendNewBlock);
    disconnect(&drawing, &DrawingLogic::sendNewBlockIdToSession, &screenController, &ScreenController::receiveNewBlockId);

    disconnect(&screenController, &ScreenController::getMindMapInSessionData, &drawing, &DrawingLogic::getMindMapInSession);
    disconnect(&drawing, &DrawingLogic::updateMindMapDataInSession, &screenController, &ScreenController::receiveMindMapDataInSession);

    disconnect(&drawing, &DrawingLogic::addNewBlock, &screenController, &ScreenController::receiveBlock);
    disconnect(&drawing, &DrawingLogic::deleteBlock, &screenController, &ScreenController::receiveDeltedBlockId);

    disconnect(&screenController, &ScreenController::sessionClosed, this, &LogicController::disconnectSession);
}

void LogicController::changeSettings(const ViewDataStructures::SettingsData &settings) {
    QRegularExpression rxNum(REG_NUM);
    QRegularExpression rxIp(REG_IP);
    if (!rxNum.match(settings.serverPort).hasMatch() || !rxIp.match(settings.serverIP).hasMatch()) {
        emit changeSettingsFailed(SETTINGS_ERROR_MSG);
        return;
    }

    HttpClientData::SettingsData convSettings = convertSettings(settings);
    HttpClientData::returnCode rc = network->updateSettings(convSettings);

    if (rc == HttpClientData::SUCCESS) {
        emit changeSettingsSuccess();
    } else {
        emit changeSettingsFailed(SETTINGS_ERROR_MSG);
    }
}

void LogicController::createNewSession(const ViewDataStructures::SessionCreationData &session) {
    if (session.password != session.repeatPassword) {
        emit sessionCreationFailed(NEW_SESSION_ERROR_MSG);
        return;
    }

    HttpClientData::SessionCreationData convSession = convertNewSession(session);
    size_t sessionId = network->createSession(convSession, user.getUser());

    if (sessionId == 0) {
        emit sessionCreationFailed(NEW_SESSION_ERROR_MSG);
    } else {
        emit sessionCreationSuccess(ViewDataStructures::SessionData(sessionId, session.name));
    }
}

void LogicController::connectToSession(const ViewDataStructures::SessionConnectionData &session) {
    QRegularExpression rxNum(REG_NUM);
    if (!rxNum.match(session.id).hasMatch()) {
        emit sessionConnectionFailed(EXIST_SESSION_ERROR_MSG);
        return;
    }

    HttpClientData::SessionConnectionData convSession = convertExistSession(session);
    std::string sessionName = network->checkConnectionToSession(convSession, user.getUser());

    if (sessionName.empty()) {
        emit sessionConnectionFailed(EXIST_SESSION_ERROR_MSG);
    } else {
        emit sessionConnectionSuccess(ViewDataStructures::SessionData(session.id.toInt(), QString::fromStdString(sessionName)));
    }
}

void LogicController::disconnectSession(const size_t sessionId) {
    network->disconnectSession(user.getUser(), sessionId);
}

void LogicController::receiveNewBlock(const HttpClientData::Block &block) {
    drawing.sendReceivedNewBlock(block);
}

void LogicController::receiveDeletedBlock(size_t id) {
    drawing.sendReceivedDeletedBlock(id);
}

HttpClientData::SettingsData LogicController::convertSettings(const ViewDataStructures::SettingsData &settings) {
    return HttpClientData::SettingsData(settings.serverIP.toStdString(), settings.serverPort.toInt());
}

HttpClientData::SessionCreationData LogicController::convertNewSession(const ViewDataStructures::SessionCreationData &session) {
    return HttpClientData::SessionCreationData(session.name.toStdString(), session.password.toStdString());
}

HttpClientData::SessionConnectionData LogicController::convertExistSession(const ViewDataStructures::SessionConnectionData &session) {
    return HttpClientData::SessionConnectionData(session.id.toInt(), session.password.toStdString());
}

