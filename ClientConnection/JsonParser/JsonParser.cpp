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

    // TODO
    result["color_background"] = "#69a832";
    result["color_border"] = "#69a832";
    result["font"] = "Arial";
    result["color_text"] = "#69a832";
    
    return result;
}
