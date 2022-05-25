#ifndef HTTP_CLIENT_DATA_HPP
#define HTTP_CLIENT_DATA_HPP

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
        std::string hex;
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
        int port;
    };

    struct SessionConnectionData
    {
        size_t id;
        std::string password;
    };

    struct SessionCreationData
    {
        std::string name;
        std::string password;
    };

    struct MindMapData
    {
        std::vector<Block> blocks;
    };
};

#endif // HTTP_CLIENT_DATA_HPP