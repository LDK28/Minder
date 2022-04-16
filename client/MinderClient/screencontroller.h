#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QObject>
#include <QDebug>

#include "datastructures.h"

#include "authorizationwindow.h"
#include "registerwindow.h"
#include "settingswindow.h"
#include "sessionconnectionwindow.h"
#include "sessioncreationwindow.h"

#include "sessionwindow.h"
#include "sessionuserlist.h"
#include "toolspalette.h"

class ScreenController: public QObject
{
    Q_OBJECT
public:
    explicit ScreenController(QObject *parent = nullptr);
    ~ScreenController();
    ScreenController(const ScreenController &) = delete;
    ScreenController(ScreenController &&) = delete;
    ScreenController& operator=(const ScreenController &) = delete;
    ScreenController& operator=(ScreenController &&) = delete;

signals: // to logic controller
    // from auth window

    void validateLoginData(LoginData data);

    // from register window

    void validateRegisterData(RegisterData data);

    // from settings window

    void saveSettings(SettingsData data);

    // from session creation window

    void createNewSession(SessionCreationData data);

    // from session connection window

    void connectToSession(SessionConnectionData data);

    // from screen controller

    void getUsersInSession();

public slots: // from logic contloller
    void validationLoginDataSuccess();
    void validationRegisterDataSuccess();
    void savingSettingsSuccess();
    void connectionToSessionSuccess();
    void creationNewSessionSuccess();
    void receiveUsersListInSession(const UsersInSessionData &data);

private slots:
    // from auth window

    void openRegisterWindow();
    void closeAuthorizationWindow();

    // from register window

    void openLoginWindow();
    void closeRegisterWindow();

    // from settings window

    void openSettingsWindow();
    void closeSettingsWindow();

    // from session creation window

    void openSessionConnectionWindow();
    void closeSessionCreationWindow();

    // from session connection window

    void openSessionCreationWindow();
    void closeSessionConnectionWindow();

    // from session window

    void closeSessionWindow();

signals:
    // to session window
    void updateUsersList(const UsersInSessionData &data);

private:
    void initConnections();
    AuthorizationWindow authWindow;
    RegisterWindow regWindow;
    SettingsWindow settingsWindow;
    SessionConnectionWindow sessionConnectionWindow;
    SessionCreationWindow sessionCreationWindow;
    SessionWindow sessionWindow;
};

#endif // SCREENCONTROLLER_H
