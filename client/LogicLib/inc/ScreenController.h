#ifndef SCREENCONTROLLER_H
#define SCREENCONTROLLER_H

#include "DataStructures.h"

class ScreenController: public QObject {
Q_OBJECT
public:
    explicit ScreenController() = default;
    ~ScreenController() = default;

signals:
//    void transmitLoginData(const LoginData &data);
//    void transmitRegisterData(const RegisterData &data);
    void transmitSettings(const ViewDataStructures::SettingsData &data);
    void transmitCreationNewSession(const ViewDataStructures::SessionCreationData &data);
    void transmitConnectionToSession(const ViewDataStructures::SessionConnectionData &data);
    void sendNewBlock(const ViewDataStructures::Block &newBlock);
    void sessionClosed();
//    void getUsersInSessionData(const size_t sessionId);
    void getMindMapInSessionData(const size_t sessionId);

public slots:
    void validationLoginDataSuccess();
    void validationRegisterDataSuccess();
    void savingSettingsSuccess();
    void savingSettingsFailed();
    void connectionToSessionSuccess(const ViewDataStructures::SessionData &data);
    void connectionToSessionFailed();
    void creationNewSessionSuccess(const ViewDataStructures::SessionData &data);
    void creationNewSessionFailed();
    //void receiveUsersListInSession(const UsersInSessionData &data);
    void receiveMindMapDataInSession(const ViewDataStructures::MindMapData &data);
    void receiveNewBlockId(const long newBlockId);
    void receiveBlock(const ViewDataStructures::Block& block);
    void receiveDeletedBlockId(size_t id);
};

#endif // SCREENCONTROLLER_H
