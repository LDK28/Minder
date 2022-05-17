#include "JsonParser.hpp"

struct FeatureName JsonParser::jsonToStruct(json data) {}
json JsonParser::structToJson(struct FeatureName data) {}
json JsonParser::SessionConnectionDataToJson(const HttpClientData::SessionConnectionData &scData){
    json result;
    result["id"] = scData.id;
    result["password"] = scData.password;
    return result;
};
