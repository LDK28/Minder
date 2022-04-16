#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

 #include <QObject>
#include <QString>
#include <QList>

typedef struct SessionConnectionData
{
    QString sessionID;
    QString sessionPassword;
} SessionConnectionData;

typedef struct SessionCreationData
{
    QString sessionName;
    QString sessionPassword;
    QString sessionRepeatPassword;
} SessionCreationData;

typedef struct LoginData
{
    QString nickname;
    QString password;
} LoginData;

typedef struct RegisterData
{
    QString nickname;
    QString password;
    QString repeatPassword;
} RegisterData;

typedef struct SettingsData
{
    QString serverIP;
    QString serverPort;
} SettingsData;

typedef struct SessionData
{

} SessionData;

typedef struct User
{
    QString nickname;
    User(const QString &nickname) : nickname(nickname) {}
} User;

typedef struct UsersInSessionData
{
    QList<User> users;
} UsersInSessionData;

#endif // DATASTRUCTURES_H
