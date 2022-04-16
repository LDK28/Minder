#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "ClientData.h"

class HttpClient {
public:
    HttpClient() = default;
    ~HttpClient() = default;

    returnCode sendNewSettings(Settings &);
    returnCode checkConnectionToSession(Session &);
    returnCode createSession(Session &);
    void getUsers(UsersList);
    void changeDesk();
    void getCurrentStateDesk();
};

#endif // HTTPCLIENT_H

