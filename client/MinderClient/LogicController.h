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
    void validateLoginData(const ViewDataStructures::LoginData data);
    void validateRegisterData(const ViewDataStructures::RegisterData data);
    void saveSettings(const ViewDataStructures::SettingsData data);
    void validateSessionCreationData(const ViewDataStructures::SessionCreationData data);
    void validateSessionConnectionData(const ViewDataStructures::SessionConnectionData data);
    void requestUpdateUsersListInSession();
    void sendNewBlock(const ViewDataStructures::Block &newBlock);
    void sendDeletedBlock(const ViewDataStructures::MindMapData &changedBlocks);
    void requestUpdateMindMapInSession(const size_t sessionId);
    void userDisconnected();

signals:
    void validationLoginDataSuccess();
    void validationRegisterDataSuccess();
    void savingSettingsSuccess();
    void sessionCreationSuccess(const ViewDataStructures::SessionData &data);
    void sessionConnectionSuccess(const ViewDataStructures::SessionData &data);
    void updateUsersListInSession(const ViewDataStructures::UsersInSessionData &data);
    void sendNewBlockIdToSession(const size_t newBlockId);
    void updateMindMapDataInSession(const ViewDataStructures::MindMapData &data);


private:
    ScreenController screenController;
};

#endif // LOGICCONTROLLER_H
