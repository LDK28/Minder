#ifndef NETWORK_SESSION_HPP
#define NETWORK_SESSION_HPP

#include "NetworkSession.hpp"

class NetworkSession
{
private:
public:
    NetworkSession(/* args */){};
    ~NetworkSession(){};

    int getSocket();
    int processRequest(char &request);
};

#endif