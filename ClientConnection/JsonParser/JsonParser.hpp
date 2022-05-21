#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "JsonParser.hpp"
#include "json.hpp"
#include "HttpClientData.hpp"

using json = nlohmann::json;

namespace JsonParser
{
    json SessionConnectionDataToJson(const HttpClientData::SessionConnectionData &scData);
    json SessionCreationDataToJson(const HttpClientData::SessionCreationData &scData);
};

#endif