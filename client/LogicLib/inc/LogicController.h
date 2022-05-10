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
        screenController(nullptr) {}
    explicit LogicController(HttpClient *network_, ScreenController *screenController_ = nullptr) :
        network(network_), user(network_), drawing(network_),
        screenController(screenController_) {}
    ~LogicController() = default;
    void connectView();
    void disconnectView();

public slots:
    void changeSettings(const ViewDataStructures::SettingsData &data);
    void createNewSession(const ViewDataStructures::SessionCreationData &data);
    void connectToSession(const ViewDataStructures::SessionConnectionData &data);
//    void getUsersListInSession();
    void disconnectSession();
    void receiveNewBlock(const HttpClientData::Block &block);
    void receiveDeletedBlock(size_t id);

signals:
    void changeSettingsSuccess();
    void changeSettingsFailed();
    void sessionCreationSuccess(const ViewDataStructures::SessionData &data);
    void sessionCreationFailed();
    void sessionConnectionSuccess(const ViewDataStructures::SessionData &data);
    void sessionConnectionFailed();
    //void updateUsersListInSession(const UsersInSessionData &data);

private:
    HttpClient *network = nullptr;
    UserLogic user;
    DrawingLogic drawing;
    std::shared_ptr <ScreenController> screenController;
    //size_t userID;

    HttpClientData::SettingsData convertSettings(const ViewDataStructures::SettingsData &settings);
    HttpClientData::SessionCreationData convertNewSession(const ViewDataStructures::SessionCreationData &session);
    HttpClientData::SessionConnectionData convertExistSession(const ViewDataStructures::SessionConnectionData &session);
};

#endif // LOGICCONTROLLER_H
