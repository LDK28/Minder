#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include <QObject>
#include <QDebug>

#include "DataStructures.h"

#include "AuthorizationWindow.h"
#include "RegisterWindow.h"
#include "SettingsWindow.h"
#include "SessionConnectionWindow.h"
#include "SessionCreationWindow.h"

#include "SessionWindow.h"
#include "SessionUsersList.h"
#include "ToolsPalette.h"
#include "NewBlockCreationWindow.h"

using namespace ViewDataStructures;

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

    void transmitLoginData(const ViewDataStructures::LoginData &data);

    // from register window

    void transmitRegisterData(const ViewDataStructures::RegisterData &data);

    // from settings window

    void transmitSettings(const ViewDataStructures::SettingsData &data);

    // from session creation window

    void transmitCreationNewSession(const ViewDataStructures::SessionCreationData &data);

    // from session connection window

    void transmitConnectionToSession(const ViewDataStructures::SessionConnectionData &data);

    // from session window

    void sendNewBlock(const ViewDataStructures::Block &newBlock);
    void transmitDeletedBlock(const ViewDataStructures::MindMapData & changedBlocks);
    void sessionClosed();

    // from screen controller

    void getUsersInSessionData(const size_t sessionId);
    void getMindMapInSessionData(const size_t sessionId);

public slots: // from logic contloller
    void validationLoginDataSuccess();
    void validationRegisterDataSuccess();
    void savingSettingsSuccess();
    void connectionToSessionSuccess(const ViewDataStructures::SessionData &data);
    void creationNewSessionSuccess(const ViewDataStructures::SessionData &data);
    void receiveUsersListInSession(const ViewDataStructures::UsersInSessionData &data);
    void receiveMindMapDataInSession(const ViewDataStructures::MindMapData &data);
    void receiveNewBlockId(const long newBlockId);
    void receiveBlock(const ViewDataStructures::Block& block);
    void receiveDeltedBlockId(const size_t id);

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

    friend class test_ScreenController;
};

#endif // SCREENCONTROLLER_H
