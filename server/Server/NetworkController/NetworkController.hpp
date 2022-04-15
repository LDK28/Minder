#ifndef NETWORK_CONTROLLER_HPP
#define NETWORK_CONTROLLER_HPP

#include <iostream>

#include "NetworkController.hpp"
#include "json.hpp"

using json = nlohmann::json;

class NetworkController
{
private:
    /* data */
public:
    NetworkController(/* args */){};
    ~NetworkController(){};

    void getRequest(std::string &request);
    void sendResponse(std::string &response);
    void sendData(json);
    void getData(json);
};

#endif