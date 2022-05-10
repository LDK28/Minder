#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "ClientData.h"

class HttpClient {
public:
    HttpClient() = default;
    virtual ~HttpClient() = default;

    virtual HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &) = 0;
    virtual std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &) = 0;
    virtual size_t createSession(const HttpClientData::SessionCreationData &) = 0;
    //void getUsers(UsersList);
    virtual void addBlock(const HttpClientData::Block &) = 0;
    virtual void changeBlock(const HttpClientData::Block &) = 0;
    virtual void deleteBlock(size_t) = 0;
    virtual HttpClientData::MindMapData getCurrentStateDesk(const size_t) = 0;
    virtual void disconnect() = 0;
};

#endif // HTTPCLIENT_H

