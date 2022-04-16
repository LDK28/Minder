#ifndef TESTSLOGICCONTROLLER_H
#define TESTSLOGICCONTROLLER_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "LogicController.h"
#include "mockClient.h"

class MockHttpClient;

TEST(LogicController, connectToSessionSuccess) {
  MockHttpClient network;

  Session session = {"67152", "", "pq7st26"};
  EXPECT_CALL(network, checkConnectionToSession(session)).Times(1);

  LogicController controller(&network);
  SessionConnectionData connectionData = {"67152", "pq7st26"};
  controller.connectToSession(connectionData);
  EXPECT_STRNE(session.name.c_str(), "");
}

TEST(LogicController, connectToSessionFailed) {
  MockHttpClient network;

  Session session = {"aaaaa", "", "pq7st26"};
  EXPECT_CALL(network, checkConnectionToSession(session)).Times(0);

  LogicController controller(&network);
  SessionConnectionData connectionData = {"aaaaa", "pq7st26"};
  controller.connectToSession(connectionData);
  EXPECT_STREQ(session.name.c_str(), "");
}

TEST(LogicController, createNewSessionSuccess) {
  MockHttpClient network;
  Session session = {"", "Room_1", "pq7st26"};
  EXPECT_CALL(network, createSession(session)).Times(1);

  LogicController controller(&network);

  SessionCreationData creationData = {"Room_1", "pq7st26", "pq7st26"};
  controller.createNewSession(creationData);
}

TEST(LogicController, createNewSessionFailed) {
  MockHttpClient network;
  Session session = {"", "Room_1", "pq7st26"};
  EXPECT_CALL(network, createSession(session)).Times(0);

  LogicController controller(&network);

  SessionCreationData creationData = {"Room_1", "pq7st26", "abareb"};
  controller.createNewSession(creationData);
}

#endif // TESTSLOGICCONTROLLER_H
