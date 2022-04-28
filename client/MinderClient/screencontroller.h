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
#include "newblockcreationwindow.h"

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

    // Interface
signals: // to logic controller
    // from auth window

    void transmitLoginData(const LoginData &data);

    // from register window

    void transmitRegisterData(const RegisterData &data);

    // from settings window

    void transmitSettings(const SettingsData &data);

    // from session creation window

    void transmitCreationNewSession(const SessionCreationData &data);

    // from session connection window

    void transmitConnectionToSession(const SessionConnectionData &data);

    // from session window

    void sendNewBlock(const Block &newBlock);
    void transmitDeletedBlock(const MindMapData & changedBlocks);
    void sessionClosed();

    // from screen controller

    void getUsersInSessionData(const size_t sessionId);
    void getMindMapInSessionData(const size_t sessionId);

public slots: // from logic contloller
    void validationLoginDataSuccess();
    void validationRegisterDataSuccess();
    void savingSettingsSuccess();
    void connectionToSessionSuccess(const SessionData &data);
    void creationNewSessionSuccess(const SessionData &data);
    void receiveUsersListInSession(const UsersInSessionData &data);
    void receiveMindMapDataInSession(const MindMapData &data);
    void receiveNewBlockId(const long newBlockId);
    void receiveBlock(const Block& block);

    // end Interface

private slots:
    // from auth window

    void openRegisterWindow();
    void closeAuthorizationWindow();
    void openSettingsWindow();

    // from register window

    void openLoginWindow();
    void closeRegisterWindow();

    // from settings window

    void closeSettingsWindow();

    // from session creation window

    void openSessionConnectionWindow();
    void closeSessionCreationWindow();

    // from session connection window

    void openSessionCreationWindow();
    void closeSessionConnectionWindow();

    // from session window

    void closeSessionWindow();

private:
    void initConnections();
    void initSessionConnections();
    void deinitSessionConnections();

private:
    AuthorizationWindow authWindow;
    RegisterWindow regWindow;
    SettingsWindow settingsWindow;
    SessionConnectionWindow sessionConnectionWindow;
    SessionCreationWindow sessionCreationWindow;
    SessionWindow *sessionWindow;
};

#endif // SCREENCONTROLLER_H
