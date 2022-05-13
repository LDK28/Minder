#pragma once
#include <string>

#include "json.hpp"

using json = nlohmann::json;

class DatabaseClient {
 public:
    virtual json createTable(json) = 0;
    virtual json dropTable(std::string) = 0;
    virtual json update(json) = 0;
    virtual json insert(json) = 0;
    virtual json select(json) = 0;
    virtual json remove(json) = 0;
    virtual json query(std::string) = 0;
};
