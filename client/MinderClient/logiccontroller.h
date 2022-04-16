#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QList>

#include "datastructures.h"
#include "screencontroller.h"

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

signals:
    void validationLoginDataSuccess();
    void validationRegisterDataSuccess();
    void savingSettingsSuccess();
    void sessionCreationSuccess();
    void sessionConnectionSuccess();
    void updateUsersListInSession(const UsersInSessionData &data);


private:
    ScreenController screenController;
};

#endif // LOGICCONTROLLER_H
