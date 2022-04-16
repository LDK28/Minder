#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "JsonParser.hpp"
#include "json.hpp"

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
};

#endif