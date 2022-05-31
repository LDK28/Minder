#ifndef TESTSLOGICCONTROLLER_H
#define TESTSLOGICCONTROLLER_H

#include "LogicController.h"
#include "mockClient.h"

TEST(LogicController, changeSettingsSuccess) {
  MockHttpClient network;

  HttpClientData::SettingsData settings("120.210.120.210", 8000);
  EXPECT_CALL(network, updateSettings(settings)).Times(1);

  LogicController controller(&network);
  ViewDataStructures::SettingsData newSettings("120.210.120.210", "8000");
  controller.changeSettings(newSettings);
}

TEST(LogicController, changeSettingsFailedIP) {
  MockHttpClient network;

  HttpClientData::SettingsData settings;
  EXPECT_CALL(network, updateSettings(settings)).Times(0);

  LogicController controller(&network);
  ViewDataStructures::SettingsData newSettings("skvjkjvbsa", "8000");
  controller.changeSettings(newSettings);
}

TEST(LogicController, changeSettingsFailedPort) {
  MockHttpClient network;

  HttpClientData::SettingsData settings;
  EXPECT_CALL(network, updateSettings(settings)).Times(0);

  LogicController controller(&network);
  ViewDataStructures::SettingsData newSettings("120.210.120.210", "khsvbd");
  controller.changeSettings(newSettings);
}

TEST(LogicController, createNewSessionSuccess) {
  MockHttpClient network;

  HttpClientData::SessionCreationData session("Room_1", "pq7st26");
  EXPECT_CALL(network, createSession(session, 0)).Times(1);

  LogicController controller(&network);

  ViewDataStructures::SessionCreationData creationData("Room_1", "pq7st26", "pq7st26");
  controller.createNewSession(creationData);
}

TEST(LogicController, createNewSessionFailed) {
  MockHttpClient network;

  HttpClientData::SessionCreationData session;
  EXPECT_CALL(network, createSession(session, 0)).Times(0);

  LogicController controller(&network);

  ViewDataStructures::SessionCreationData creationData("Room_1", "pq7st26", "abareb");
  controller.createNewSession(creationData);
}

TEST(LogicController, connectToSessionSuccess) {
  MockHttpClient network;

  HttpClientData::SessionConnectionData session(67152, "pq7st26");
  EXPECT_CALL(network, checkConnectionToSession(session, 0)).Times(1);

  LogicController controller(&network);
  ViewDataStructures::SessionConnectionData connectionData("67152", "pq7st26");
  controller.connectToSession(connectionData);
}

TEST(LogicController, connectToSessionFailed) {
  MockHttpClient network;

  HttpClientData::SessionConnectionData session;
  EXPECT_CALL(network, checkConnectionToSession(session, 0)).Times(0);

  LogicController controller(&network);
  ViewDataStructures::SessionConnectionData connectionData("aaaaa", "pq7st26");
  controller.connectToSession(connectionData);
}

TEST(LogicController, disconnectSession) {
  MockHttpClient network;

  size_t sessionId = 1;
  EXPECT_CALL(network, disconnectSession(0, sessionId)).Times(1);

  LogicController controller(&network);
  controller.disconnectSession(sessionId);
}

#endif // TESTSLOGICCONTROLLER_H
