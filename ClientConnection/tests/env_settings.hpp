#ifndef ENV_SETTINGS_HPP
#define ENV_SETTINGS_HPP

#include <gtest/gtest.h>

#include "JsonParser.hpp"
#include "json.hpp"
#include "ClientData.h"

using json = nlohmann::json;

HttpClientData::SessionConnectionData SESSION_CONNECTION_DATA_STRUCT{12, "12345"};
// <=>
json SESSION_CONNECTION_DATA_JSON = {{"id", 12}, {"password", "12345"}};

HttpClientData::SessionCreationData SESSION_CREATION_DATA_STRUCT{"name", "12345"};
// <=>
json SESSION_CREATION_DATA_JSON = {{"name", "name"}, {"password", "12345"}};

#endif