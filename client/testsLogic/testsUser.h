#ifndef TESTSUSER_H
#define TESTSUSER_H

#include "mockClient.h"
#include "User.h"

class MockHttpClient;

TEST(User, getUsers) {
  MockHttpClient network;

  UsersList users = {};
  EXPECT_CALL(network, sendNewSettings(users)).Times(1);

  User user(&network);
  Users recUsers = {};
  user.getUsers(recUsers);
}

#endif // TESTSUSER_H
