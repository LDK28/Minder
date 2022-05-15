#include "LogicController.h"
int testBlockId = 0;
#include <time.h>
#include <random>

LogicController::LogicController(QObject *parent)
    : QObject{parent}
{
    connect(&screenController, &ScreenController::transmitLoginData, this, &LogicController::validateLoginData);
    connect(this, &LogicController::validationLoginDataSuccess, &screenController, &ScreenController::validationLoginDataSuccess);

    connect(&screenController, &ScreenController::transmitRegisterData, this, &LogicController::validateRegisterData);
    connect(this, &LogicController::validationRegisterDataSuccess, &screenController, &ScreenController::validationRegisterDataSuccess);

    connect(&screenController, &ScreenController::transmitSettings, this, &LogicController::saveSettings);
    connect(this, &LogicController::savingSettingsSuccess, &screenController, &ScreenController::savingSettingsSuccess);

    connect(&screenController, &ScreenController::transmitCreationNewSession, this, &LogicController::validateSessionCreationData);
    connect(this, &LogicController::sessionCreationSuccess, &screenController, &ScreenController::creationNewSessionSuccess);

    connect(&screenController, &ScreenController::transmitConnectionToSession, this, &LogicController::validateSessionConnectionData);
    connect(this, &LogicController::sessionConnectionSuccess, &screenController, &ScreenController::connectionToSessionSuccess);

    connect(&screenController, &ScreenController::getUsersInSessionData, this, &LogicController::requestUpdateUsersListInSession);
    connect(this, &LogicController::updateUsersListInSession, &screenController, &ScreenController::receiveUsersListInSession);

    connect(&screenController, &ScreenController::getMindMapInSessionData, this, &LogicController::requestUpdateMindMapInSession);
    connect(this, &LogicController::updateMindMapDataInSession, &screenController, &ScreenController::receiveMindMapDataInSession);

    connect(&screenController, &ScreenController::sendNewBlock, this, &LogicController::sendNewBlock);
    connect(this, &LogicController::sendNewBlockIdToSession, &screenController, &ScreenController::receiveNewBlockId);

    connect(&screenController, &ScreenController::sessionClosed, this, &LogicController::userDisconnected);

    connect(&screenController, &ScreenController::transmitDeletedBlock, this, &LogicController::sendDeletedBlock);

}

void LogicController::validateLoginData(LoginData data)
{
    qDebug() << "Logic controller: validation login data test(success): " << data.nickname << " " << data.password;

    emit validationLoginDataSuccess();
//    screenController.validationLoginDataFailure("123");
}

void LogicController::validateRegisterData(RegisterData data)
{
    qDebug() << "Logic controller: validation register data test(success): " << data.nickname << " " << data.password << " " << data.repeatPassword;

    emit validationRegisterDataSuccess();
}

void LogicController::saveSettings(SettingsData data)
{
    qDebug() << "Logic controller: saving settings test(success): " << data.serverIP << " " << data.serverPort;
    emit savingSettingsSuccess();
}

void LogicController::validateSessionCreationData(SessionCreationData data)
{
    qDebug() << "Logic controller: session creation test(success): " << data.name << " " << data.password << " " << data.repeatPassword;
    emit sessionCreationSuccess(SessionData());
}

void LogicController::validateSessionConnectionData(SessionConnectionData data)
{
    qDebug() << "Logic controller: session connection test(success): " << data.id << " " << data.password;

    srand(time(NULL));
    SessionData sdata;
    sdata.id = rand() % 1000;
    sdata.name = QString("Room") + QString::number(sdata.id);
    emit sessionConnectionSuccess(sdata);
}

void LogicController::requestUpdateUsersListInSession()
{
    QList<User> ulist;
    srand(time(NULL));
    for(int i = 0; i < 1 + rand() % (10 - 1); ++i)
    {
        ulist.append(QString("Test User ") + QString::number(i + 1));
    }
    UsersInSessionData data = {ulist};

    emit updateUsersListInSession(data);
}


void LogicController::sendNewBlock(const Block &newBlock)
{
//    Q_UNUSED(newBlock);

    // test getting new block from this user

    qDebug() << "Logic controller receive new block";

    emit sendNewBlockIdToSession(++testBlockId);

    // test getting new block from another user
    qDebug() << "Another user get block";
    Block b = newBlock;
    b.id = ++testBlockId;
    b.position = newBlock.position - QPoint(10,10);
//    screenController.receiveBlock(b);
//    screenController.receiveDeltedBlockId(b.id);
}

void LogicController::requestUpdateMindMapInSession(const size_t sessionId)
{
    Q_UNUSED(sessionId);
    qDebug() << "Logic controller: update mindmap data";

    MindMapData data;
    srand(time(NULL));
    for(int i = 0; i < 1 + rand() % (6 - 1); ++i)
    {
        Block b;
        b.parentId = i == 0 ? 0 : testBlockId;
        b.id = ++testBlockId;
        b.position = QPoint(100 * i, 100 * i);
        b.text = QString("Block from DB: id = ") + QString::number(b.id) + QString(" par id ") + QString::number(b.parentId) + QString(" text ") + QString::number(i);
        data.blocks.append(b);
    }

    emit updateMindMapDataInSession(data);
}

void LogicController::userDisconnected()
{
    qDebug() << "Logic controlled: user disconnected";
}

void LogicController::sendDeletedBlock(const MindMapData &changedBlocks)
{
    qDebug() << "Logic controller: send deleted block";
    qDebug() << "Deleted block: ";
    qDebug() << changedBlocks.blocks.at(0).id;
    qDebug() << "Changed blocks:";
    for(int i = 1; i < changedBlocks.blocks.count(); ++i)
    {
        changedBlocks.blocks.at(i).print();
    }
}
