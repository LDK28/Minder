#include "JsonParser.hpp"

json JsonParser::SessionConnectionDataToJson(const HttpClientData::SessionConnectionData &scData)
{
    json result;
    result["id"] = scData.id;
    result["password"] = scData.password;
    return result;
};

json JsonParser::SessionCreationDataToJson(const HttpClientData::SessionCreationData &scData)
{
    json result;
    result["name"] = scData.name;
    result["password"] = scData.password;
    return result;
};

json JsonParser::BlockToJson(const HttpClientData::Block &block)
{
    json result;
    result["id"] = block.id;
    result["parent_id"] = block.parentId;
    result["x"] = block.posX;
    result["y"] = block.posY;
    result["txt"] = block.text;
    result["color_background"] = block.bgColor.name;
    result["color_border"] = block.borderColor.name;
    result["font"] = block.font.name;
    result["color_text"] = block.fontColor.name;

    return result;
}

json JsonParser::UserDataToJson(const HttpClientData::UserData &userData)
{
    json result;

    result["nickname"] = userData.nickname;
    result["password"] = userData.password;

    return result;
}

HttpClientData::Block JsonParser::JsonToBlock(const json &block)
{
    HttpClientData::Block result;

    result.id = block["id"];
    result.parentId = block["parent_id"];
    result.posX = block["x"];
    result.posY = block["y"];
    result.text = block["txt"];
    result.bgColor.name = block["color_background"];
    result.borderColor.name = block["color_border"];
    result.font.name = block["font"];
    result.fontColor.name = block["color_text"];

    return result;
}
