#ifndef SERVER_LOGIC_HPP
#define SERVER_LOGIC_HPP

#include "ServerLogic.hpp"

#include "BuisnessLogic.hpp"

#include "json.hpp"

#include <set>

using json = nlohmann::json;

struct LastUpdate
{
    size_t sessionId;
    size_t userId;
};

class BaseLogic
{
private:
public:
    virtual std::string router(std::string &request) = 0;
};

class ServerLogic : BaseLogic
{
private:
    BuisnessLogic buisnessLogic;

    std::set<LastUpdate> lastUpdate;
public:
    std::string router(std::string &request) override;
};

#endif