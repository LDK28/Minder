#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <iostream>

#include "HttpClient.hpp"
#include "JsonParser.hpp"

class HttpClient
{
private:
    json parseToJson(struct FeatureName data);
    struct FeatureName parseToStruct(json);

    void sendRequest(std::string request);
    json getResponce();
    void parseResponce(json);
public:
    HttpClient(/* args */){};
    ~HttpClient(){};

    void sendNewSettings(struct FeatureName);
    int checkConnectionToSession(int confID);
    struct FeatureName getUsers(std::string request);
    void addUser(struct FeatureName);
    void changeDesk(struct FeatureName);
    struct FeatureName getCurrentStateDesk(std::string request);
    struct FeatureName getData(std::string request);
    void sendData(struct FeatureName);
};
#endif