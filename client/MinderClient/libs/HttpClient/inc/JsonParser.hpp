#ifndef JSON_PARSER_HPP
#define JSON_PARSER_HPP

#include "json.hpp"
#include "HttpDataStructures.h"

using json = nlohmann::json;

namespace JsonParser
{
    json SessionConnectionDataToJson(const HttpClientData::SessionConnectionData &scData);
    json SessionCreationDataToJson(const HttpClientData::SessionCreationData &scData);
    json BlockToJson(const HttpClientData::Block &block);
    json UserDataToJson(const HttpClientData::UserData &userData);
    HttpClientData::Block JsonToBlock(const json &block);
};

#endif
