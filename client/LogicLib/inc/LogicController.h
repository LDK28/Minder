#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "LogicLib_global.h"

#include <QtWidgets>

#include <QTimer>

#include "DataStructures.h"
#include "DrawingLogic.h"
#include "UserLogic.h"
#include "ScreenController.h"

class LOGICLIB_EXPORT LogicController: public QObject {
    Q_OBJECT
public:
    explicit LogicController();
    explicit LogicController(HttpClient *network_);
    ~LogicController() = default;

public slots:
    void changeSettings(const ViewDataStructures::SettingsData &data);
    void createNewSession(const ViewDataStructures::SessionCreationData &data);
    void connectToSession(const ViewDataStructures::SessionConnectionData &data);
    void disconnectSession(const size_t sessionId);

private slots:
    void pingServer();

signals:
    void changeSettingsSuccess();
    void changeSettingsFailed(const QString &);
    void sessionCreationSuccess(const ViewDataStructures::SessionData &data);
    void sessionCreationFailed(const QString &);
    void sessionConnectionSuccess(const ViewDataStructures::SessionData &data);
    void sessionConnectionFailed(const QString &);
    void block();
    void unblock();

private:
    HttpClient *network;
    QTimer *timer;
    UserLogic user;
    DrawingLogic drawing;
    ScreenController screenController;

    void connectView();

    size_t sessionId;

    HttpClientData::SettingsData convertSettings(const ViewDataStructures::SettingsData &settings);
    HttpClientData::SessionCreationData convertNewSession(const ViewDataStructures::SessionCreationData &session);
    HttpClientData::SessionConnectionData convertExistSession(const ViewDataStructures::SessionConnectionData &session);
};

#endif // LOGICCONTROLLER_H
