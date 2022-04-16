#include <gtest/gtest.h>

#include "json.hpp"

using json = nlohmann::json;

#include "DatabaseDrawDeskClient.h"

TEST(getDeskData, testBasic) {
    int deskId = 1;
    json expectedResponse = {{"id", 1},
                             {"elements",
                              {"block:",
                               {
                                   {"x", 5},
                                   {"y", 5},
                                   {"width", 5},
                                   {"height", 5},
                               }}}};

    DatabaseDrawDeskClient client;
    json response = client.getDeskData(deskId);
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}

TEST(updateDeskData, testBasic) {
    json expectedResponse = {{"id", 1},
                             {"elements",
                              {"block:",
                               {
                                   {"x", 5},
                                   {"y", 5},
                                   {"width", 5},
                                   {"height", 5},
                               }}}};

    DatabaseDrawDeskClient client;
    json response = client.updateDeskData(expectedResponse);
    EXPECT_STREQ(expectedResponse.dump().c_str(), response.dump().c_str());
}
