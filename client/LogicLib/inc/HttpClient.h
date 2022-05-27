#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "ClientData.h"

class HttpClient {
public:
    HttpClient() = default;
    virtual ~HttpClient() = default;

    virtual HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &) = 0;
    virtual std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &, const size_t &userId) = 0;
    virtual size_t createSession(const HttpClientData::SessionCreationData &, const size_t &userId) = 0;
    virtual void disconnect(const size_t &userId, const size_t &sessionId) = 0;

    virtual size_t addBlock(const HttpClientData::Block &, const size_t &deskId) = 0;
    virtual void changeBlock(const HttpClientData::Block &) = 0;
    virtual void deleteBlock(const size_t &blockId) = 0;
    virtual HttpClientData::MindMapData getCurrentStateDesk(const size_t &sessionID) = 0;

    virtual HttpClientData::UsersInSessionData getUsersInSession(const size_t &sessionId) = 0;
    virtual size_t loginUser(const HttpClientData::UserData &) = 0;
    virtual size_t registerUser(const HttpClientData::UserData &) = 0;
};

#endif // HTTPCLIENT_H

