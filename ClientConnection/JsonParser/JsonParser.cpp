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
    result["bgColor"] = block.bgColor;
    result["borderColor"] = block.borderColor;
    result["font"] = block.font;
    result["fontColor"] = block.fontColor;
    return result;
}
