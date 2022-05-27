#include "JsonParser.hpp"

json JsonParser::SessionConnectionDataToJson(const HttpClientData::SessionConnectionData &scData){
    json result;
    result["id"] = scData.id;
    result["password"] = scData.password;
    return result;
};

json JsonParser::SessionCreationDataToJson(const HttpClientData::SessionCreationData &scData){
    json result;
    result["name"] = scData.name;
    result["password"] = scData.password;
    return result;
};

json JsonParser::BlockToJson(const HttpClientData::Block &block){
    json result;
    result["id"] = block.id;
    result["parentId"] = block.parentId;
    result["posX"] = block.posX;
    result["posY"] = block.posY;
    result["text"] = block.text;
    result["color_background"] = block.bgColor.name;
    result["color_border"] = block.borderColor.name;
    result["font"] = block.font.name;
    result["color_text"] = block.fontColor.name;
    
    return result;
}

std::string nickname;
        std::string password;

json JsonParser::UserDataToJson(const HttpClientData::UserData &userData){
    json result;

    result["nickname"] = userData.nickname;
    result["password"] = userData.password;

    return result;
}