#ifndef MOCKCLIENT_H
#define MOCKCLIENT_H

#include "HttpClient.h"

class MockHttpClient : public HttpClient {
public:
  MOCK_METHOD(HttpClientData::returnCode, updateSettings, (const HttpClientData::SettingsData &));
  MOCK_METHOD(std::string, checkConnectionToSession, (const HttpClientData::SessionConnectionData &, const size_t &));
  MOCK_METHOD(size_t, createSession, (const HttpClientData::SessionCreationData &, const size_t &));
  MOCK_METHOD(void, disconnect, (const size_t &, const size_t &));

  MOCK_METHOD(size_t, addBlock, (const HttpClientData::Block &, const size_t &));
  MOCK_METHOD(void, changeBlock, (const HttpClientData::Block &));
  MOCK_METHOD(void, deleteBlock, (const size_t &));
  MOCK_METHOD(HttpClientData::MindMapData, getCurrentStateDesk, (const size_t &));

  MOCK_METHOD(HttpClientData::UsersInSessionData, getUsersInSession, (const size_t &));
  MOCK_METHOD(size_t, loginUser, (const HttpClientData::LoginData &));
  MOCK_METHOD(size_t, registerUser, (const HttpClientData::RegisterData &));
};

#endif // MOCKCLIENT_H
