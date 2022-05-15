#include "ScreenController.h"

ScreenController::ScreenController(QObject *parent):
    QObject{parent},
    sessionWindow(nullptr)
{
    initConnections();
    authWindow.show();
}

ScreenController::~ScreenController()
{
    qDebug() << "Screen controller destructor";

    if(sessionWindow)
    {
        deinitSessionConnections();
        delete sessionWindow;
        sessionWindow = nullptr;
    }
}

void ScreenController::initConnections()
{
    // from auth window
    connect(&authWindow, &AuthorizationWindow::on_closeAuthorizationWindowButtonClicked, this, &ScreenController::closeAuthorizationWindow);
    connect(&authWindow, &AuthorizationWindow::on_openRegisterWindowButtonClicked, this, &ScreenController::openRegisterWindow);
    connect(&authWindow, &AuthorizationWindow::on_openSettingsWindowButtonClicked, this, &ScreenController::openSettingsWindow);
    connect(&authWindow, &AuthorizationWindow::on_login, this, &ScreenController::transmitLoginData);

    // from register window
    connect(&regWindow, &RegisterWindow::on_closeRegisterWindowButtonClicked, this, &ScreenController::closeRegisterWindow);
    connect(&regWindow, &RegisterWindow::on_openLoginWindowButtonCLicked, this, &ScreenController::openLoginWindow);
    connect(&regWindow, &RegisterWindow::on_register, this, &ScreenController::transmitRegisterData);

    // from settings window
    connect(&settingsWindow, &SettingsWindow::on_closeSettingsWindowButtonClicked, this, &ScreenController::closeSettingsWindow);
    connect(&settingsWindow, &SettingsWindow::on_saveSettings, this, &ScreenController::transmitSettings);

    // from session creation window
    connect(&sessionCreationWindow, &SessionCreationWindow::on_closeSessionCreationWindowButtonClicked, this, &ScreenController::closeSessionCreationWindow);
    connect(&sessionCreationWindow, &SessionCreationWindow::on_openSessionConnectionWindowButtonClicked, this, &ScreenController::openSessionConnectionWindow);
    connect(&sessionCreationWindow, &SessionCreationWindow::on_createNewSession, this, &ScreenController::transmitCreationNewSession);

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

///////////////////auth window////////////////////////////

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

void ScreenController::validationLoginDataSuccess()
{
    qDebug() << "Screen controller: login success";

    authWindow.close();
    sessionConnectionWindow.show();
}

void ScreenController::validationLoginDataFailure(const QString &errMsg)
{
    qDebug() << "Screen controller: login fail";

    authWindow.showErrorMsg(errMsg);
}

//////////////// register window///////////////////////////////

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

void ScreenController::validationRegisterDataSuccess()
{
    qDebug() << "Screen controller: register  success";

    regWindow.close();
    authWindow.show();
}

void ScreenController::validationRegisterDataFailure(const QString &errMsg)
{
    qDebug() << "Screen controller: register fail";

    regWindow.showErrorMsg(errMsg);
}

//////////////////////////// settings window //////////////////////////////////////////////////

void ScreenController::closeSettingsWindow()
{
    qDebug() << "Screen controller: accepted close event from SettingsWindow";

    settingsWindow.close();
    authWindow.show();
}


void ScreenController::savingSettingsSuccess()
{
    qDebug() << "Screen controller: saving settings success";

    settingsWindow.close();
    authWindow.show();
}

void ScreenController::savingSettingsFailure(const QString &errMsg)
{
    qDebug() << "Screen controller: saving settings fail";

    settingsWindow.showErrorMsg(errMsg);
}

//////////////////////////////// session creation window ////////////////////////////////////////

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

void ScreenController::creationNewSessionSuccess(const ViewDataStructures::SessionData &data)
{
    qDebug() << "Screen controller: creation new session success";

    sessionCreationWindow.close();

    sessionWindow = new SessionWindow(data);
    initSessionConnections();

    sessionWindow->show();
}

void ScreenController::creationNewSessionFailure(const QString &errMsg)
{
    qDebug() << "Screen controller: creation session fail";

    sessionCreationWindow.showErrorMsg(errMsg);
}

///////////////////////////////////// session connection window////////////////////////////////////////////////

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

void ScreenController::connectionToSessionSuccess(const ViewDataStructures::SessionData &data)
{
    qDebug() << "Screen controller: connection to existing session success";

    sessionConnectionWindow.close();

    sessionWindow = new SessionWindow(data);
    initSessionConnections();

    sessionWindow->show();
}

void ScreenController::connectionToSessionFailure(const QString &errMsg)
{
    qDebug() << "Screen controller: connection to session fail";

    sessionConnectionWindow.showErrorMsg(errMsg);
}

/////////////////////////////////////////// session window///////////////////////////////////////////

void ScreenController::closeSessionWindow()
{
    qDebug() << "Screen controller: accepted close event from SessionWindow";

    deinitSessionConnections();
    delete sessionWindow;
    sessionWindow = nullptr;

    sessionConnectionWindow.show();
}

void ScreenController::receiveUsersListInSession(const ViewDataStructures::UsersInSessionData &data)
{
    qDebug() << "Screen controller: receieved users list for SessionWidnow";
    //
    sessionWindow->updateUsersList(data);
}

void ScreenController::receiveMindMapDataInSession(const ViewDataStructures::MindMapData &data)
{
    qDebug() << "Screen controller: receive new mindmap data";

    assert(sessionWindow);
    sessionWindow->updateMindMap(data);
}

void ScreenController::receiveNewBlockId(const long newBlockId)
{
    qDebug() << "Screen controller: receiver new block id " << newBlockId;

    assert(sessionWindow != nullptr);
    sessionWindow->setNewBlockId(newBlockId);
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
