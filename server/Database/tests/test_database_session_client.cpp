#include <gtest/gtest.h>

#include "json.hpp"

using json = nlohmann::json;

#include "DatabaseSessionClient.h"

TEST(createSession, testBasic) {
    json expectedResponse = {{"id", 1}};

    DatabaseSessionClient client;
    int userId = 3;
    json response = client.createSession();
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}

TEST(addUsersInSession, testBasic) {
    json expectedResponse = {{"users_id", {1, 2, 3}}};

    DatabaseSessionClient client;
    json request = {{"users_id", {2, 3}}};
    json response = client.addUsersInSession(request);
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}

TEST(checkSession, testBasic) {
    json expectedResponse = true;

    DatabaseSessionClient client;
    int sessionId = 1;
    bool response = client.checkSession(sessionId);
    EXPECT_EQ(expectedResponse, response);
}

TEST(updateSession, testBasic) {
    json expectedResponse = {{"id", 3}, {"draw_desk_id", 2}, {"users_id", {1, 2, 3}}};

    DatabaseSessionClient client;
    json request = {{"id", 3}, {"draw_desk_id", 2}, {"users_id", {1, 2, 3}}};
    json response = client.updateSession(request);
    EXPECT_EQ(expectedResponse, response);
}

TEST(getSessionInfo, testBasic) {
    json expectedResponse = {{"id", 3}, {"draw_desk_id", 2}, {"users_id", {1, 2, 3}}};

    DatabaseSessionClient client;
    int sessionId = 3;
    json response = client.getSessionInfo(sessionId);
    EXPECT_EQ(expectedResponse, response);
}

TEST(selectSessionsWithUser, testBasic) {
    json expectedResponse = {{"session_id", {1, 2, 3}}};

    DatabaseSessionClient client;
    int userId = 3;
    json response = client.selectSessionsWithUser(userId);
    EXPECT_EQ(expectedResponse, response);
}


TEST(deleteSession, testBasic) {
    json expectedResponse = {{"id", 3}, {"draw_desk_id", 2}, {"users_id", {1, 2, 3}}};

    DatabaseSessionClient client;
    int sessionId = 3;
    json response = client.selectSessionsWithUser(sessionId);
    EXPECT_EQ(expectedResponse, response);
}
