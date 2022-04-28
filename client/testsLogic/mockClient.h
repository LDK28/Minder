#ifndef MOCKCLIENT_H
#define MOCKCLIENT_H

#include "HttpClient.h"

class MockHttpClient : public HttpClient {
public:
  MOCK_METHOD(returnCode, updateSettings, (const Settings &));
  MOCK_METHOD(std::string, checkConnectionToSession, (const ExistSession &));
  MOCK_METHOD(size_t, createSession, (const NewSession &));
  MOCK_METHOD(void, addBlock, (const BlockData &));
  MOCK_METHOD(ListBlocks, getCurrentStateDesk, (const size_t));
  MOCK_METHOD(void, disconnect, ());
};

#endif // MOCKCLIENT_H
