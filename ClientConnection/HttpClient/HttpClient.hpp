#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <iostream>

#include <sys/socket.h> // connect, AF_INET
#include <netdb.h>      // gethostbyname
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h>
#include <unistd.h> 

#include "HttpClient.hpp"
#include "JsonParser.hpp"
#include "HttpClientData.hpp"

#define BUFFER_SIZE 512

class HttpClient
{
private:
    virtual std::string sendRequest(std::string request) = 0;

public:
    HttpClient(/* args */){};
    ~HttpClient(){};

    virtual void sendNewSettings(struct FeatureName) = 0;
    virtual int checkConnectionToSession(int confID) = 0;
    virtual struct FeatureName getUsers(std::string request) = 0;
    virtual void addUser(struct FeatureName) = 0;
    virtual void changeDesk(struct FeatureName) = 0;
    virtual struct FeatureName getCurrentStateDesk(std::string request) = 0;
    virtual struct FeatureName getData(std::string request) = 0;
    virtual void sendData(struct FeatureName) = 0;
};

class InterfaceHttpClient : HttpClient
{
private:
    int sd;

    std::string sendRequest(std::string request) override;
    int connectServer();
    int sendMsg(std::string msg);
    std::string recvMsg();

public:
    InterfaceHttpClient(/* args */){};
    ~InterfaceHttpClient(){};

    // void sendNewSettings(struct FeatureName);
    // int checkConnectionToSession(int confID);
    // struct FeatureName getUsers(std::string request);
    // void addUser(struct FeatureName);
    // void changeDesk(struct FeatureName);
    // struct FeatureName getCurrentStateDesk(std::string request);
    // struct FeatureName getData(std::string request);
    // void sendData(struct FeatureName);

    HttpClientData::MidnMapData getMap(HttpClientData::SessionConnectionData con);
};
#endif