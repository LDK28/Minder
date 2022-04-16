#include <gtest/gtest.h>
#include "JsonParser.hpp"

using json = nlohmann::json;

TEST(ServerLogic, jsonToStruct)
{
    EXPECT_EQ(struct FeatureName{}, jsonToStruct(json));
}

TEST(ServerLogic, structToJson);
{
    EXPECT_EQ(json, structToJson(struct FeatureName{}));
}