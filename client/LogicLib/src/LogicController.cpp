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

    connect(&drawing, &DrawingLogic::addNewBlock, screenController.get(), &ScreenController::receiveBlock);
    connect(&drawing, &DrawingLogic::deleteBlock, screenController.get(), &ScreenController::receiveDeletedBlockId);

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

    disconnect(&drawing, &DrawingLogic::addNewBlock, screenController.get(), &ScreenController::receiveBlock);
    disconnect(&drawing, &DrawingLogic::deleteBlock, screenController.get(), &ScreenController::receiveDeletedBlockId);

    disconnect(screenController.get(), &ScreenController::sessionClosed, this, &LogicController::disconnectSession);
}

void LogicController::changeSettings(const ViewDataStructures::SettingsData &settings) {
    QRegExp rxNum(regNum);
    QRegExp rxIp(regIP);
    if (!rxNum.exactMatch(settings.serverPort) || !rxIp.exactMatch(settings.serverIP)) {
        emit sessionConnectionFailed();
        return;
    }

    HttpClientData::SettingsData convSettings = convertSettings(settings);
    HttpClientData::returnCode rc = network->updateSettings(convSettings);

    if (rc == HttpClientData::SUCCESS) {
        emit changeSettingsSuccess();
    } else {
        emit changeSettingsFailed();
    }
}

void LogicController::createNewSession(const ViewDataStructures::SessionCreationData &session) {
    if (session.password != session.repeatPassword) {
        emit sessionCreationFailed();
        return;
    }

    HttpClientData::SessionCreationData convSession = convertNewSession(session);
    size_t sessionId = network->createSession(convSession);

    if (sessionId == 0) {
        emit sessionCreationFailed();
    } else {
        emit sessionCreationSuccess(ViewDataStructures::SessionData(sessionId, session.name));
    }
}

void LogicController::connectToSession(const ViewDataStructures::SessionConnectionData &session) {
    QRegExp rxNum(regNum);
    if (!rxNum.exactMatch(session.id)) {
        emit sessionConnectionFailed();
        return;
    }

    HttpClientData::SessionConnectionData convSession = convertExistSession(session);
    std::string sessionName = network->checkConnectionToSession(convSession);

    if (sessionName.empty()) {
        emit sessionConnectionFailed();
    } else {
        emit sessionConnectionSuccess(ViewDataStructures::SessionData(session.id.toInt(), QString::fromStdString(sessionName)));
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

void LogicController::receiveNewBlock(const HttpClientData::Block &block) {
    drawing.sendReceivedNewBlock(block);
}

void LogicController::receiveDeletedBlock(size_t id) {
    drawing.sendReceivedDeletedBlock(id);
}

HttpClientData::SettingsData LogicController::convertSettings(const ViewDataStructures::SettingsData &settings) {
    return HttpClientData::SettingsData(settings.serverIP.toStdString(), settings.serverPort.toStdString());
}

HttpClientData::SessionCreationData LogicController::convertNewSession(const ViewDataStructures::SessionCreationData &session) {
    return HttpClientData::SessionCreationData(session.name.toStdString(), session.password.toStdString());
}

HttpClientData::SessionConnectionData LogicController::convertExistSession(const ViewDataStructures::SessionConnectionData &session) {
    return HttpClientData::SessionConnectionData(session.id.toInt(), session.password.toStdString());
}

