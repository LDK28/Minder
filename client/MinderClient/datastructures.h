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

#define DEF_SCALE 100

#define BZOOMPLUS_D 20
#define BZOOMMINUS_D -20

#define WZOOMPLUS_D 5
#define WZOOMMINUS_D -5

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
    int id;
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

    size_t id;
    size_t parentId;
    QPoint position;
    int type;

    QString text;

    QFont textFont;
    QColor textColor;
    QColor borderColor;
    QColor backgroundColor;

    Block() : id(0), parentId(0), position(QPoint(0, 0)), textColor(Qt::black), borderColor(Qt::red), backgroundColor(Qt::yellow) {}
    Block(const Block& sBlock) = default;
    Block& operator = (const Block &sBlock) = default;
    Block(Block&& sBlock) = default;
    Block& operator = (Block &&sBlock) = default;

    void print() const
    {
        qDebug() << "->Block: " <<  this->id << " " << this->parentId << " " << this->position;
    }
};

struct MindMapData
{
    QList<Block> blocks;
};

#endif // DATASTRUCTURES_H
