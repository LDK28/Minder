#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "ClientData.h"

class HttpClient {
public:
    HttpClient() = default;
    ~HttpClient() = default;

    returnCode updateSettings(const Settings &);
    std::string checkConnectionToSession(const ExistSession &);
    size_t createSession(const NewSession &);
    //void getUsers(UsersList);
    void addBlock(const BlockData &);
    ListBlocks getCurrentStateDesk(const size_t);
    void disconnect();
};

#endif // HTTPCLIENT_H

