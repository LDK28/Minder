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

const int defaultScalePercent = 100;
const int btnZoomPlusDeltaScalePercent = 20;
const int btnZoomMinusDeltaScalePercent = -20;
const int wheelZoomPlusDeltaScalePercent = 5;
const int wheelZoomMinusDeltaScalePercent = -5;

namespace ViewDataStructures
{

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

    explicit SettingsData() = default;
    explicit SettingsData(const QString &serverIP_, const QString &serverPort_) :
        serverIP(serverIP_), serverPort(serverPort_) {}
};

struct SessionConnectionData
{
    QString id;
    QString password;

    explicit SessionConnectionData() = default;
    explicit SessionConnectionData(const QString &id_, const QString &password_) :
        id(id_), password(password_) {}
};

struct SessionCreationData
{
    QString name;
    QString password;
    QString repeatPassword;

    explicit SessionCreationData() = default;
    explicit SessionCreationData(const QString &name_, const QString &password_, const QString &repeatPassword_) :
        name(name_), password(password_), repeatPassword(repeatPassword_) {}
};

struct SessionData
{
    size_t id;
    QString name;

    explicit SessionData() : id(0), name() {}
    explicit SessionData(size_t id_, const QString &name_) : id(id_), name(name_) {}
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
    size_t id;
    size_t parentId;
    QPoint position;
    int type;

    QString text;

    QFont textFont;
    QColor textColor;
    QColor borderColor;
    QColor backgroundColor;

    explicit Block() : id(0), parentId(0), position(QPoint(0, 0)), type(0), text(), textFont(),
        textColor(Qt::black), borderColor(Qt::red), backgroundColor(Qt::yellow) {}

    explicit Block(size_t id_, size_t parentId_, const QPoint &pos, const QString &text_,
                   const QFont &font, const QColor &textColor_, const QColor &borderColor_, const QColor &bgColor, int type_ = 0) :
        id(id_), parentId(parentId_), position(pos), type(type_), text(text_), textFont(font),
        textColor(textColor_), borderColor(borderColor_), backgroundColor(bgColor) {}

    void print() const
    {
        qDebug() << this->id << " " << this->parentId << " " << this->position;
    }
};

struct MindMapData
{
    QList<Block> blocks;

    explicit MindMapData() = default;
};
}

#endif // DATASTRUCTURES_H
