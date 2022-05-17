#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "JsonParser.hpp"
#include "json.hpp"
#include "HttpClientData.hpp"

using json = nlohmann::json;

struct FeatureName
{
};

class JsonParser
{
private:
    /* data */
public:
    JsonParser(/* args */){};
    ~JsonParser(){};

    struct FeatureName jsonToStruct(json data);
    json structToJson(struct FeatureName data);
    json SessionConnectionDataToJson(const HttpClientData::SessionConnectionData &scData);

};

#endif