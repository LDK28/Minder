#include <iostream>

struct HttpClientData
{
public:
    struct Font
    {
        std::string family;
        int pointSize;
        int weight;
        bool italic;
    };

    struct Color
    {
        int r;
        int g;
        int b;
    };

    struct Block
    {
        size_t id;
        size_t parentId;
        int posX;
        int posY;
        std::string text;
        Font font;
        Color fontColor;
        Color borderColor;
        Color bgColor;
    };

    enum returnCode
    {
        SUCCESS,
        FAILED
    };

    struct SettingsData
    {
        std::string ip;
        std::string port;
    };

    struct SessionConnectionData
    {
        size_t id;
        std::string password;
    };

    struct MidnMapData
    {
        std::vector<Block> blocks;
    };
};
