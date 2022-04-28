#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QList>

#include "DataStructures.h"
#include "ScreenController.h"

using namespace ViewDataStructures;

class LogicController: public QObject
{
    Q_OBJECT
public:
    explicit LogicController(QObject *parent = nullptr);

private slots:
    void validateLoginData(LoginData data);
    void validateRegisterData(RegisterData data);
    void saveSettings(SettingsData data);
    void validateSessionCreationData(SessionCreationData data);
    void validateSessionConnectionData(SessionConnectionData data);
    void requestUpdateUsersListInSession();
    void sendNewBlock(const Block &newBlock);
    void sendDeletedBlock(const MindMapData &changedBlocks);
    void requestUpdateMindMapInSession(const long sessionId);
    void userDisconnected();

signals:
    void validationLoginDataSuccess();
    void validationRegisterDataSuccess();
    void savingSettingsSuccess();
    void sessionCreationSuccess(const SessionData &data);
    void sessionConnectionSuccess(const SessionData &data);
    void updateUsersListInSession(const UsersInSessionData &data);
    void sendNewBlockIdToSession(const long newBlockId);
    void updateMindMapDataInSession(const MindMapData &data);


private:
    ScreenController screenController;
};

#endif // LOGICCONTROLLER_H
