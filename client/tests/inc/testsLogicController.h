#ifndef TESTSLOGICCONTROLLER_H
#define TESTSLOGICCONTROLLER_H

#include "LogicController.h"
#include "mockClient.h"

TEST(LogicController, changeSettingsSuccess) {
  std::shared_ptr <MockHttpClient> network(new MockHttpClient);

  Settings settings("120.210.120.210", "8000");
  EXPECT_CALL(*network, updateSettings(settings)).Times(1);

  LogicController controller(network);
  SettingsData newSettings("120.210.120.210", "8000");
  controller.changeSettings(newSettings);
}

TEST(LogicController, changeSettingsFailedIP) {
  std::shared_ptr <MockHttpClient> network(new MockHttpClient);

  Settings settings;
  EXPECT_CALL(*network, updateSettings(settings)).Times(0);

  LogicController controller(network);
  SettingsData newSettings("skvjkjvbsa", "8000");
  controller.changeSettings(newSettings);
}

TEST(LogicController, changeSettingsFailedPort) {
  std::shared_ptr <MockHttpClient> network(new MockHttpClient);

  Settings settings;
  EXPECT_CALL(*network, updateSettings(settings)).Times(0);

  LogicController controller(network);
  SettingsData newSettings("120.210.120.210", "khsvbd");
  controller.changeSettings(newSettings);
}

TEST(LogicController, createNewSessionSuccess) {
  std::shared_ptr <MockHttpClient> network(new MockHttpClient);

  NewSession session("Room_1", "pq7st26");
  EXPECT_CALL(*network, createSession(session)).Times(1);

  LogicController controller(network);

  SessionCreationData creationData("Room_1", "pq7st26", "pq7st26");
  controller.createNewSession(creationData);
}

TEST(LogicController, createNewSessionFailed) {
  std::shared_ptr <MockHttpClient> network(new MockHttpClient);

  NewSession session;
  EXPECT_CALL(*network, createSession(session)).Times(0);

  LogicController controller(network);

  SessionCreationData creationData("Room_1", "pq7st26", "abareb");
  controller.createNewSession(creationData);
}

TEST(LogicController, connectToSessionSuccess) {
  std::shared_ptr <MockHttpClient> network(new MockHttpClient);

  ExistSession session(67152, "pq7st26");
  EXPECT_CALL(*network, checkConnectionToSession(session)).Times(1);

  LogicController controller(network);
  SessionConnectionData connectionData("67152", "pq7st26");
  controller.connectToSession(connectionData);
}

TEST(LogicController, connectToSessionFailed) {
  std::shared_ptr <MockHttpClient> network(new MockHttpClient);

  ExistSession session;
  EXPECT_CALL(*network, checkConnectionToSession(session)).Times(0);

  LogicController controller(network);
  SessionConnectionData connectionData("aaaaa", "pq7st26");
  controller.connectToSession(connectionData);
}

TEST(LogicController, disconnectSession) {
  std::shared_ptr <MockHttpClient> network(new MockHttpClient);

  EXPECT_CALL(*network, disconnect()).Times(1);

  LogicController controller(network);
  controller.disconnectSession();
}

#endif // TESTSLOGICCONTROLLER_H
