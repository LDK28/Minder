#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include "LogicLib_global.h"

#include <QtWidgets>

#include "DataStructures.h"
#include "Drawing.h"
#include "User.h"

class LOGICLIB_EXPORT LogicController: public QObject {
Q_OBJECT
public:
    explicit LogicController() = default;
    explicit LogicController(HttpClient *network_) : network(network_), user(network_), drawing(network_) {}
    ~LogicController() = default;
    void connectView();
    void disconnectView();
public slots:
    void connectToSession(SessionConnectionData &);
    void createNewSession(const SessionCreationData &);
    void changeSettings(const SettingsData &settings);
signals:
    void sessionConnectionSuccess();
    void sessionConnectionFailed();
private:
    std::shared_ptr <HttpClient> network = nullptr;
    User user;
    Drawing drawing;
};

#endif // LOGICCONTROLLER_H
