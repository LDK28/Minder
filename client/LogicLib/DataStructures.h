#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QString>

struct SessionConnectionData
{
    QString sessionID;
    QString sessionPassword;
};

struct SessionCreationData
{
    QString sessionName;
    QString sessionPassword;
    QString sessionRepeatPassword;
};

//struct LoginData
//{
//    QString nickname;
//    QString password;
//};

//struct RegisterData
//{
//    QString nickname;
//    QString password;
//    QString repeatPassword;
//};

struct SettingsData
{
    QString serverIP;
    QString serverPort;
};

struct UserData
{
    QString name;
};

struct Users {
    QList<UserData> users;
};

#endif // DATASTRUCTURES_H
