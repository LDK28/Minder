#include "ScreenController.h"

ScreenController::ScreenController(QObject *parent):
    QObject{parent},
    sessionWindow(nullptr)
{
    initConnections();
    authWindow.show();
    //    sessionWindow.show();
}

ScreenController::~ScreenController()
{
    qDebug() << "Screen controller destructor";
}

void ScreenController::initConnections()
{
    // from auth window
    connect(&authWindow, &AuthorizationWindow::on_closeAuthorizationWindowButtonClicked, this, &ScreenController::closeAuthorizationWindow);
    connect(&authWindow, &AuthorizationWindow::on_openRegisterWindowButtonClicked, this, &ScreenController::openRegisterWindow);
    connect(&authWindow, &AuthorizationWindow::on_openSettingsWindowButtonClicked, this, &ScreenController::openSettingsWindow);

    connect(&authWindow, &AuthorizationWindow::on_login, this, &ScreenController::transmitLoginData);

    // to auth window

    // from register window
    connect(&regWindow, &RegisterWindow::on_closeRegisterWindowButtonClicked, this, &ScreenController::closeRegisterWindow);
    connect(&regWindow, &RegisterWindow::on_openLoginWindowButtonCLicked, this, &ScreenController::openLoginWindow);

    connect(&regWindow, &RegisterWindow::on_register, this, &ScreenController::transmitRegisterData);

    // to register window


    // from settings window
    connect(&settingsWindow, &SettingsWindow::on_closeSettingsWindowButtonClicked, this, &ScreenController::closeSettingsWindow);

    connect(&settingsWindow, &SettingsWindow::on_saveSettings, this, &ScreenController::transmitSettings);

    // to settings window

    // from session creation window

    connect(&sessionCreationWindow, &SessionCreationWindow::on_closeSessionCreationWindowButtonClicked, this, &ScreenController::closeSessionCreationWindow);
    connect(&sessionCreationWindow, &SessionCreationWindow::on_openSessionConnectionWindowButtonClicked, this, &ScreenController::openSessionConnectionWindow);

    connect(&sessionCreationWindow, &SessionCreationWindow::on_createNewSession, this, &ScreenController::transmitCreationNewSession);

    // to session creation window

    // from session connection window

    connect(&sessionConnectionWindow, &SessionConnectionWindow::on_closeSessionConnectionWindowButtonClicked, this, &ScreenController::closeSessionConnectionWindow);
    connect(&sessionConnectionWindow, &SessionConnectionWindow::on_openNewSessionCreationWindowButtonClicked, this, &ScreenController::openSessionCreationWindow);

    connect(&sessionConnectionWindow, &SessionConnectionWindow::on_connectToSession, this, &ScreenController::transmitConnectionToSession);
}

void ScreenController::initSessionConnections()
{
    connect(sessionWindow, &SessionWindow::on_closeSessionWindowButtonClicked, this, &ScreenController::closeSessionWindow);
    connect(sessionWindow, &SessionWindow::transmitNewBlock, this, &ScreenController::sendNewBlock);
    connect(sessionWindow, &SessionWindow::transmitDeletedBlock, this, &ScreenController::transmitDeletedBlock);
    connect(sessionWindow, &SessionWindow::getUsersListData, this, &ScreenController::getUsersInSessionData);
    connect(sessionWindow, &SessionWindow::getMindMapData, this, &ScreenController::getMindMapInSessionData);

}

void ScreenController::deinitSessionConnections()
{
    disconnect(sessionWindow, &SessionWindow::on_closeSessionWindowButtonClicked, this, &ScreenController::closeSessionWindow);
    disconnect(sessionWindow, &SessionWindow::transmitNewBlock, this, &ScreenController::sendNewBlock);
    disconnect(sessionWindow, &SessionWindow::transmitDeletedBlock, this, &ScreenController::transmitDeletedBlock);
    disconnect(sessionWindow, &SessionWindow::getUsersListData, this, &ScreenController::getUsersInSessionData);
    disconnect(sessionWindow, &SessionWindow::getMindMapData, this, &ScreenController::getMindMapInSessionData);
}

// Screen controller

void ScreenController::receiveUsersListInSession(const ViewDataStructures::UsersInSessionData &data)
{
    qDebug() << "Screen controller: receieved users list for SessionWidnow";
    assert(sessionWindow);
    sessionWindow->updateUsersList(data);
}

// from auth window

void ScreenController::closeAuthorizationWindow()
{
    qDebug() << "Screen controller: accepted close event from AuthWindow";

    authWindow.close();
}

void ScreenController::openRegisterWindow()
{
    qDebug() << "Screen controller: accepted open register window event from AuthWindow";

    authWindow.close();
    regWindow.show();
}

void ScreenController::openSettingsWindow()
{
    qDebug() << "Screen controller: accepted open settings window event from AuthWindow";

    authWindow.close();
    settingsWindow.show();
}

// from register window

void ScreenController::closeRegisterWindow()
{
    qDebug() << "Screen controller: accepted close event from RegisterWindow";

    regWindow.close();
    authWindow.show();
}

void ScreenController::openLoginWindow()
{
    qDebug() << "Screen controller: accepted open login window event from RegisterWindow";
    regWindow.close();
    authWindow.show();
}

// from settings window

void ScreenController::closeSettingsWindow()
{
    qDebug() << "Screen controller: accepted close event from SettingsWindow";

    settingsWindow.close();
    authWindow.show();
}

// from session creation window

void ScreenController::closeSessionCreationWindow()
{
    qDebug() << "Screen controller: accepted close event from SessionCreationWindow";

    sessionCreationWindow.close();
}

void ScreenController::openSessionConnectionWindow()
{
    qDebug() << "Screen controller: accepted open session connection event from SessionCreationWindow";

    sessionCreationWindow.close();
    sessionConnectionWindow.show();
}

// from session connection window

void ScreenController::closeSessionConnectionWindow()
{
    qDebug() << "Screen controller: accepted close event from SessionConnectionWindow";

    sessionConnectionWindow.close();
}

void ScreenController::openSessionCreationWindow()
{
    qDebug() << "Screen controller: accepted open session creation event from SessionConnectionWindow";

    sessionConnectionWindow.close();
    sessionCreationWindow.show();
}

// from session connection window

void ScreenController::closeSessionWindow()
{
    qDebug() << "Screen controller: accepted close event from SessionWindow";

//    deinitSessionConnections();
    delete sessionWindow;
    sessionWindow = nullptr;

    sessionConnectionWindow.show();
}



// from logic controller

void ScreenController::validationLoginDataSuccess()
{
    qDebug() << "Screen controller: login success";

    authWindow.close();
    sessionConnectionWindow.show();
}

void ScreenController::validationRegisterDataSuccess()
{
    qDebug() << "Screen controller: register  success";

    regWindow.close();
    authWindow.show();
}

void ScreenController::savingSettingsSuccess()
{
    qDebug() << "Screen controller: saving settings success";

    settingsWindow.close();
    authWindow.show();
}

void ScreenController::connectionToSessionSuccess(const ViewDataStructures::SessionData &data)
{
    qDebug() << "Screen controller: connection to existing session success";

    sessionConnectionWindow.close();

    sessionWindow = new SessionWindow(data);
    initSessionConnections();

    sessionWindow->show();
}

void ScreenController::creationNewSessionSuccess(const ViewDataStructures::SessionData &data)
{
    qDebug() << "Screen controller: creation new session success";

    sessionCreationWindow.close();

    sessionWindow = new SessionWindow(data);
    initSessionConnections();

    sessionWindow->show();
}

void ScreenController::receiveNewBlockId(const long newBlockId)
{
    qDebug() << "Screen controller: receiver new block id " << newBlockId;

    assert(sessionWindow != nullptr);
    sessionWindow->setNewBlockId(newBlockId);
}

void ScreenController::receiveMindMapDataInSession(const ViewDataStructures::MindMapData &data)
{
    qDebug() << "Screen controller: receive new mindmap data";

    assert(sessionWindow);
    sessionWindow->updateMindMap(data);
}

void ScreenController::receiveBlock(const ViewDataStructures::Block& block)
{
    qDebug() << "Screen controller: receive block";

    assert(sessionWindow);
    sessionWindow->setBlock(block);
}


void ScreenController::receiveDeltedBlockId(const size_t id)
{
    qDebug() << "Screen controller: receive deleted block from another user";

    sessionWindow->deleteBlock(id);
}
