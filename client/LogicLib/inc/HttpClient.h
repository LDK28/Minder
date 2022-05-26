#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "ClientData.h"

class HttpClient {
public:
    HttpClient() = default;
    virtual ~HttpClient() = default;

    virtual HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &) = 0;
    virtual std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &) = 0;
    virtual std::size_t createSession(const HttpClientData::SessionCreationData &) = 0;
    virtual std::size_t addBlock(const HttpClientData::Block &) = 0;
    virtual void changeBlock(const HttpClientData::Block &) = 0;
    virtual void deleteBlock(std::size_t) = 0;
    virtual HttpClientData::MindMapData getCurrentStateDesk(const size_t) = 0;
    virtual void disconnect() = 0;

    virtual HttpClientData::UsersInSessionData getUsersInSession(std::size_t) = 0;
    virtual void addUser(const HttpClientData::User &) = 0;
    virtual void deleteUser(const HttpClientData::User &) = 0;
};

#endif // HTTPCLIENT_H

