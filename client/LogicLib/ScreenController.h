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
    void transmitSettings(const SettingsData &data);
    void transmitCreationNewSession(const SessionCreationData &data);
    void transmitConnectionToSession(const SessionConnectionData &data);
    void sendNewBlock(const Block &newBlock);
    void sessionClosed();
//    void getUsersInSessionData(const size_t sessionId);
    void getMindMapInSessionData(const size_t sessionId);

public slots:
    void validationLoginDataSuccess();
    void validationRegisterDataSuccess();
    void savingSettingsSuccess();
    void savingSettingsFailed();
    void connectionToSessionSuccess(const SessionData &data);
    void connectionToSessionFailed();
    void creationNewSessionSuccess(const SessionData &data);
    void creationNewSessionFailed();
    //void receiveUsersListInSession(const UsersInSessionData &data);
    void receiveMindMapDataInSession(const MindMapData &data);
    void receiveNewBlockId(const long newBlockId);
    void receiveBlock(const Block& block);
};

#endif // SCREENCONTROLLER_H
