#include <gtest/gtest.h>
#include "ServerLogic.hpp"
#include "NetworkController.hpp"
#include "NetworkSession.hpp"

using json = nlohmann::json;

TEST(ServerLogic, getConfID)
{
    EXPECT_EQ(NULL, getConfID());
}

TEST(ServerLogic, getDataFromDB);
{
    EXPECT_EQ(json, getDataFromDB("users"));
}

TEST(ServerLogic, router);
{
    EXPECT_EQ(json, router("users", json));
}

TEST(NetworkSession, getSocket);
{
    EXPECT_EQ(1, getSocket());
}

TEST(NetworkSession, processRequest);
{
    EXPECT_EQ(1, processRequest("GET HTTP 1.0 DATA_USERS"));
}