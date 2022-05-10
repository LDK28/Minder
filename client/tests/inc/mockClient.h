#ifndef MOCKCLIENT_H
#define MOCKCLIENT_H

#include "HttpClient.h"

class MockHttpClient : public HttpClient {
public:
  MOCK_METHOD(HttpClientData::returnCode, updateSettings, (const HttpClientData::SettingsData &));
  MOCK_METHOD(std::string, checkConnectionToSession, (const HttpClientData::SessionConnectionData &));
  MOCK_METHOD(size_t, createSession, (const HttpClientData::SessionCreationData &));
  MOCK_METHOD(void, disconnect, ());

  MOCK_METHOD(void, addBlock, (const HttpClientData::Block &));
  MOCK_METHOD(HttpClientData::MindMapData, getCurrentStateDesk, (const size_t));
  MOCK_METHOD(void, changeBlock, (const HttpClientData::Block &));
  MOCK_METHOD(void, deleteBlock, (size_t));
};

#endif // MOCKCLIENT_H
