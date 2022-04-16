#ifndef MOCKCLIENT_H
#define MOCKCLIENT_H

#include "HttpClient.h"

class MockHttpClient : public HttpClient {
public:
  MOCK_METHOD(returnCode, checkConnectionToSession, (Session &));
  MOCK_METHOD(returnCode, createSession, (Session));
  MOCK_METHOD(void, changeDesk, ());
  MOCK_METHOD(returnCode, sendNewSettings, (Settings &));
  MOCK_METHOD(void, getUsers, (UsersList));
};

#endif // MOCKCLIENT_H
