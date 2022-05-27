#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "LogicLib_global.h"

#include <QtWidgets>

#include "DataStructures.h"
#include "DrawingLogic.h"
#include "UserLogic.h"
#include "ScreenController.h"

class LOGICLIB_EXPORT LogicController: public QObject {
Q_OBJECT
public:
    explicit LogicController() : network(nullptr), user(network), drawing(network),
        screenController(nullptr) { connectView(); }
    explicit LogicController(HttpClient *network_, ScreenController *screenController_ = nullptr) :
        network(network_), user(network_), drawing(network_),
        screenController(screenController_) {}
    ~LogicController() = default;

public slots:
    void changeSettings(const ViewDataStructures::SettingsData &data);
    void createNewSession(const ViewDataStructures::SessionCreationData &data);
    void connectToSession(const ViewDataStructures::SessionConnectionData &data);
    void disconnectSession(const size_t sessionId);
    void receiveNewBlock(const HttpClientData::Block &block);
    void receiveDeletedBlock(size_t id);

signals:
    void changeSettingsSuccess();
    void changeSettingsFailed(const QString &);
    void sessionCreationSuccess(const ViewDataStructures::SessionData &data);
    void sessionCreationFailed(const QString &);
    void sessionConnectionSuccess(const ViewDataStructures::SessionData &data);
    void sessionConnectionFailed(const QString &);

private:
    HttpClient *network;
    UserLogic user;
    DrawingLogic drawing;
    std::shared_ptr <ScreenController> screenController;

    void connectView();
    void disconnectView();

    HttpClientData::SettingsData convertSettings(const ViewDataStructures::SettingsData &settings);
    HttpClientData::SessionCreationData convertNewSession(const ViewDataStructures::SessionCreationData &session);
    HttpClientData::SessionConnectionData convertExistSession(const ViewDataStructures::SessionConnectionData &session);
};

#endif // LOGICCONTROLLER_H
