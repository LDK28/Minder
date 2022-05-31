#ifndef TESTSUSER_H
#define TESTSUSER_H

#include "mockClient.h"
#include "UserLogic.h"

TEST(UserLogic, getUsersListInSession) {
  MockHttpClient network;

  std::size_t sessionId = 1;
  EXPECT_CALL(network, getUsersInSession(sessionId)).Times(1);

  UserLogic user(&network);
  user.getUsersListInSession(sessionId);
}

TEST(UserLogic, loginUser) {
  MockHttpClient network;

  HttpClientData::UserData user;
  EXPECT_CALL(network, loginUser(user)).Times(1);

  ViewDataStructures::LoginData viewUser;
  UserLogic userLogic(&network);
  userLogic.loginUser(viewUser);
}

TEST(UserLogic, registerUserSuccess) {
  MockHttpClient network;

  HttpClientData::UserData newUser("Petya", "password");
  EXPECT_CALL(network, registerUser(newUser)).Times(1);

  ViewDataStructures::RegisterData viewUser("Petya", "password", "password");
  UserLogic user(&network);
  user.registerUser(viewUser);
}

TEST(UserLogic, registerUserFailed) {
  MockHttpClient network;

  HttpClientData::UserData newUser("Petya", "password");
  EXPECT_CALL(network, registerUser(newUser)).Times(0);

  ViewDataStructures::RegisterData viewUser("Petya", "password", "qwerty");
  UserLogic user(&network);
  user.registerUser(viewUser);
}

#endif // TESTSUSER_H
