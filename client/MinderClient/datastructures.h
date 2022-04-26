#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <QObject>
#include <QString>
#include <QList>
#include <QPointF>
#include <QColor>
#include <QSizeF>
#include <QDebug>
#include <QFont>

#define TYPES_ENUM(ITEM) \
    ITEM(Node) \
    ITEM(Comment)

#define MAKE_ENUM(VAR) VAR,
#define MAKE_STRINGS(VAR) #VAR,

struct LoginData
{
    QString nickname;
    QString password;
};

struct RegisterData
{
    QString nickname;
    QString password;
    QString repeatPassword;
};

struct SettingsData
{
    QString serverIP;
    QString serverPort;
};

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

struct SessionData
{
    QString sessionName;
    long sessionId;
};

struct User
{
    QString nickname;
    User(const QString &nickname) : nickname(nickname) {}
};

struct UsersInSessionData
{
    QList<User> users;
};

class Block
{
public:
    enum Type
    {
        TYPES_ENUM(MAKE_ENUM)
    };

    long id;
    long parentId;
    QPoint position;
    int type;

    QString text;

    QFont textFont;
    QColor textColor;
    QColor borderColor;
    QColor backgroundColor;

    Block() : id(-1), parentId(-1), position(QPoint(0, 0)), textColor(Qt::black), borderColor(Qt::red), backgroundColor(Qt::yellow) {}

    void print() const
    {
        qDebug() << this->id << " " << this->parentId << " " << this->position;
    }
};

struct MindMapData
{
    QList<Block> blocks;
};

#endif // DATASTRUCTURES_H
