#ifndef NETWORK_CONTROLLER_HPP
#define NETWORK_CONTROLLER_HPP

#include <iostream>
#include <sys/socket.h> // connect, AF_INET
#include <netdb.h>      // gethostbyname
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>

#include "NetworkController.hpp"
#include "ServerLogic.hpp"
#include "json.hpp"

#define BUFFER_SIZE 1024

using json = nlohmann::json;

class NetworkController
{
private:
    int sd;
    ServerLogic serverLogic;

    void sendMsg(std::string msg, int sd);
    std::string recvMsg(int sd);
public:
    
    void startServer();
};

#endif