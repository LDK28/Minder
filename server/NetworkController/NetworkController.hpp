#ifndef NETWORK_CONTROLLER_HPP
#define NETWORK_CONTROLLER_HPP

#include "NetworkController.hpp"

#include <iostream>

class NetworkController
{
private:
    /* data */
public:
    NetworkController(/* args */){};
    ~NetworkController(){};

    void getRequest(std::string &request);
    void sendResponse(std::string &response);
    void sendData(json data);
    void getData(json data);
};

#endif