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
