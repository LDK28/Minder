#include <gtest/gtest.h>

#include "json.hpp"

using json = nlohmann::json;

#include "DatabaseUsersClient.h"

TEST(create_user, testBasic) {
    json request = {{"name:", "Dima"}};
    json expectedResponse = {{"id", 1}, {"name:", "Dima"}};

    DatabaseUsersClient client;
    json response = client.createUser(request);
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}

TEST(checkUser, testBasic) {
    json request = {{"name:", "Dima"}};
    bool expectedResponse = true;

    DatabaseUsersClient client;
    bool response = client.checkUser(request);
    EXPECT_EQ(response, expectedResponse);
}

TEST(getAllUsersInfo, testBasic) {
    json expectedResponse = {
        {{"id", 1}, {"name:", "Dima"}, {"session_id", 1}},
        {{"id", 2}, {"name:", "Nastya"}, {"session_id", 1}},
        {{"id", 3}, {"name:", "Uliana"}, {"session_id", 1}}};

    DatabaseUsersClient client;
    json response = client.getAllUsersInfo();
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}

TEST(getUserInfo, testBasic) {
    json expectedResponse = {{"id", 3}, {"name:", "Uliana"}, {"session_id", 1}};

    DatabaseUsersClient client;
    int userId = 3;
    json response = client.getUserInfo(userId);
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}

TEST(selectUsersByName, testBasic) {
    std::string name("Dima");

    json expectedResponse = {
        {{"id", 1}, {"name:", name}, {"session_id", 1}},
        {{"id", 5}, {"name:", name}, {"session_id", 3}},
        {{"id", 7}, {"name:", name}, {"session_id", 9}}};

    DatabaseUsersClient client;
    json response = client.selectUsersByName(name);
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}

TEST(deleteUsersById, testBasic) {
    int userId = 3;

    json expectedResponse = {{"id", userId}, {"name:", "Uliana"}, {"session_id", 1}};

    DatabaseUsersClient client;
    json response = client.deleteUsersById(userId);
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}
