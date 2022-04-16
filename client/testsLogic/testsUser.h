#ifndef TESTSUSER_H
#define TESTSUSER_H

#include "mockClient.h"
#include "User.h"

class MockHttpClient;

void changeSettings(SettingsData &settings);
void getUsers(Users &users);

TEST(User, changeSettingsSuccess) {
  MockHttpClient network;

  Settings settings = {"120.210.120.210", "8000"};
  EXPECT_CALL(network, sendNewSettings(settings)).Times(1);

  User user(&network);
  SettingsData newSettings = {"120.210.120.210", "8000"};
  user.changeSettings(newSettings);
}

TEST(User, changeSettingsFailed) {
  MockHttpClient network;

  Settings settings = {"skvjkjvbsa", "8000"};
  EXPECT_CALL(network, sendNewSettings(settings)).Times(0);

  User user(&network);
  SettingsData newSettings = {"skvjkjvbsa", "8000"};
  user.changeSettings(newSettings);
}

TEST(User, getUsers) {
  MockHttpClient network;

  UsersList users = {};
  EXPECT_CALL(network, sendNewSettings(users)).Times(1);

  User user(&network);
  Users recUsers = {};
  user.getUsers(recUsers);
}

#endif // TESTSUSER_H
