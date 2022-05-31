#include "LogicController.h"

const char *REG_IP = "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                     "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                     "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\."
                     "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)";

const char *REG_NUM = "\\d";

const char *SETTINGS_ERROR_MSG = "Settings change failed.";
const char *NEW_SESSION_ERROR_MSG = "Session creation failed.";
const char *EXIST_SESSION_ERROR_MSG = "Session connection failed.";

LogicController::LogicController() : network(new HttpClient("127.0.0.1", 1025)), timer(new QTimer()),
    user(network, timer), drawing(network, timer) {
    connect(timer, &QTimer::timeout, this, &LogicController::pingServer);
    timer->setInterval(2000);

    sessionId = 0;

    connectView();
}

LogicController::LogicController(HttpClient *network_) : network(network_), timer(new QTimer()),
    user(network, timer), drawing(network, timer) {
    connect(timer, &QTimer::timeout, this, &LogicController::pingServer);
    timer->setInterval(2000);

    sessionId = 0;

    connectView();
}

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

    connect(&screenController, &ScreenController::sessionClosed, this, &LogicController::disconnectSession);

    connect(this, &LogicController::block, &screenController, &ScreenController::lockView);
    connect(this, &LogicController::unblock, &screenController, &ScreenController::unlockView);

    connect(&user, &UserLogic::block, &screenController, &ScreenController::lockView);
    connect(&user, &UserLogic::unblock, &screenController, &ScreenController::unlockView);

    connect(&drawing, &DrawingLogic::block, &screenController, &ScreenController::lockView);
    connect(&drawing, &DrawingLogic::unblock, &screenController, &ScreenController::unlockView);
}

void LogicController::changeSettings(const ViewDataStructures::SettingsData &settings) {
    emit block();
    QRegularExpression rxNum(REG_NUM);
    QRegularExpression rxIp(REG_IP);
    if (!rxNum.match(settings.serverPort).hasMatch() || !rxIp.match(settings.serverIP).hasMatch()) {
        emit changeSettingsFailed(SETTINGS_ERROR_MSG);
        return;
    }

    HttpClientData::SettingsData convSettings = convertSettings(settings);

    HttpClientData::returnCode rc = network->updateSettings(convSettings);

    emit unblock();
    if (rc == HttpClientData::SUCCESS) {
        emit changeSettingsSuccess();
    } else {
        emit changeSettingsFailed(SETTINGS_ERROR_MSG);
    }
}

void LogicController::createNewSession(const ViewDataStructures::SessionCreationData &session) {
    emit block();
    if (session.password != session.repeatPassword) {
        emit sessionCreationFailed(NEW_SESSION_ERROR_MSG);
        return;
    }

    HttpClientData::SessionCreationData convSession = convertNewSession(session);

    timer->stop();
    sessionId = network->createSession(convSession, user.getUser());
    timer->start();

    emit unblock();
    if (sessionId == 0) {
        emit sessionCreationFailed(NEW_SESSION_ERROR_MSG);
    } else {
        timer->start();
        emit sessionCreationSuccess(ViewDataStructures::SessionData(sessionId, session.name));
    }
}

void LogicController::connectToSession(const ViewDataStructures::SessionConnectionData &session) {
    emit block();
    QRegularExpression rxNum(REG_NUM);
    if (!rxNum.match(session.id).hasMatch()) {
        emit sessionConnectionFailed(EXIST_SESSION_ERROR_MSG);
        return;
    }

    HttpClientData::SessionConnectionData convSession = convertExistSession(session);

    std::string sessionName = network->checkConnectionToSession(convSession, user.getUser());

    emit unblock();
    if (sessionName.empty()) {
        emit sessionConnectionFailed(EXIST_SESSION_ERROR_MSG);
    } else {
        emit sessionConnectionSuccess(ViewDataStructures::SessionData(session.id.toInt(), QString::fromStdString(sessionName)));
        timer->start();
    }
}

void LogicController::disconnectSession(const size_t sessionId) {
    emit block();
    timer->stop();
    network->disconnectSession(user.getUser(), sessionId);
    emit unblock();
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

void LogicController::pingServer()
{
    if (network->ping(user.getUser(), sessionId)) {
        drawing.getMindMapInSession(sessionId);
    }
}

