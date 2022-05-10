#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <string>
#include <vector>

namespace HttpClientData {
typedef enum {
    SUCCESS, FAILED
} returnCode;

struct SessionCreationData {
    std::string name;
    std::string password;

    explicit SessionCreationData() : name(), password() {}
    explicit SessionCreationData(const std::string &name_, const std::string &password_) : name(name_), password(password_) {}

    bool operator==(const SessionCreationData& other) const {
        return name == other.name && password == other.password;
    }
};

struct SessionConnectionData {
    size_t id;
    std::string password;

    explicit SessionConnectionData() : id(0) {}
    explicit SessionConnectionData(size_t id_, const std::string &password_) : id(id_), password(password_) {}

    bool operator==(const SessionConnectionData& other) const {
        return id == other.id && password == other.password;
    }
};

struct SettingsData {
    std::string ip;
    std::string port;

    explicit SettingsData() = default;
    explicit SettingsData(const std::string &ip_, const std::string &port_) : ip(ip_), port(port_) {}

    bool operator==(const SettingsData& other) const {
        return ip == other.ip && port == other.port;
    }
};

//struct UsersList {
//    std::vector<std::string> users;

//    bool operator==(const UsersList& other) const {
//        return users == other.users;
//    }
//};

struct Font {
    std::string family;
    int pointSize;
    int weight;
    bool italic;

    explicit Font() : pointSize(-1), weight(50), italic(false) {}
    explicit Font(const std::string &family_, int pointSize_, int weight_, bool italic_) :
        family(family_), pointSize(pointSize_), weight(weight_), italic(italic_) {}

    bool operator==(const Font& other) const {
        return family == other.family && pointSize == other.pointSize
                && weight == other.weight && italic == other.italic;
    }
};

struct Color {
    int r;
    int g;
    int b;

    explicit Color() : r(0), g(0), b(0) {}
    explicit Color(int r_, int g_, int b_) : r(r_), g(g_), b(b_) {}

    bool operator==(const Color& other) const {
        return r == other.r && g == other.g && b == other.b;
    }
};

struct Block {
    size_t id;
    size_t parentId;
    int posX;
    int posY;

    std::string text;
    Font font;
    Color fontColor;
    Color borderColor;
    Color bgColor;

    explicit Block() : id(0), parentId(0), posX(0), posY(0), borderColor(255, 0, 0), bgColor(255, 255, 0) {}

    explicit Block(size_t id_, size_t parentId_, int posX_, int posY_, const std::string &text_,
        const Font &font_, const Color &fontColor_, const Color &borderColor_, const Color &bgColor_) :
        id(id_), parentId(parentId_), posX(posX_), posY(posY_), text(text_), font(font_),
        fontColor(fontColor_), borderColor(borderColor_), bgColor(bgColor_) {}

    bool operator==(const Block& other) const {
        return id == other.id && parentId == other.parentId && posX == other.posX &&
        posY == other.posY && text == other.text && font == other.font &&
        fontColor == other.fontColor && borderColor == other.borderColor && bgColor == other.bgColor;
    }
};

struct MindMapData {
    std::vector<Block> blocks;

    explicit MindMapData() = default;
};
}

#endif // CLIENTDATA_H
