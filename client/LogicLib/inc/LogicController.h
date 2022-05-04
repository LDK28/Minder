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
    explicit LogicController(const std::shared_ptr<HttpClient> &network_, ScreenController *screenController_ = nullptr) :
        network(network_), user(network_), drawing(network_),
        screenController(screenController_) {}
    ~LogicController() = default;
    void connectView();
    void disconnectView();

public slots:
    void changeSettings(const SettingsData &data);
    void createNewSession(const SessionCreationData &data);
    void connectToSession(const SessionConnectionData &data);
//    void getUsersListInSession();
    void disconnectSession();

signals:
    void changeSettingsSuccess();
    void changeSettingsFailed();
    void sessionCreationSuccess(const SessionData &data);
    void sessionCreationFailed();
    void sessionConnectionSuccess(const SessionData &data);
    void sessionConnectionFailed();
    //void updateUsersListInSession(const UsersInSessionData &data);

private:
    std::shared_ptr <HttpClient> network;
    UserLogic user;
    DrawingLogic drawing;
    std::shared_ptr <ScreenController> screenController;
    //size_t userID;

    Settings convertSettings(const SettingsData &settings);
    NewSession convertNewSession(const SessionCreationData &session);
    ExistSession convertExistSession(const SessionConnectionData &session);
};

#endif // LOGICCONTROLLER_H
