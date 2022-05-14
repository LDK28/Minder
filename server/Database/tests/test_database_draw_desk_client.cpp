#include <gtest/gtest.h>

#include "DatabaseDrawDeskClient.h"
#include "env_settings.hpp"

TEST(get_desk_info, simpletest) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();
    int id = 1;
    json desk = cl.getDeskInfo(id);
    ASSERT_EQ(desk["status"], "ok");
    ASSERT_EQ(deskSessionIds[0], desk["desks"][0]["session_id"].get<int>());
}

TEST(create_desk, simpleCreate) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();

    json req = {{"session_id", 3}};
    json resp = cl.createDesk(req);
    // std::cout << "test create " << resp.dump(2) << std::endl;
    int id = std::stoi(resp["id"].get<std::string>());
    json desk = cl.getDeskInfo(id);
    ASSERT_EQ(req["session_id"], desk["desks"][0]["session_id"]);
}

TEST(get_blocks_info_from_desk, simpletest) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();
    // json usrs = cl.getBlocksInfoFromDesk();
    // // std::cout << usrs.dump(2) << std::endl;

    // for (int i = 0; i < usernames.size(); i++) {
    //     ASSERT_EQ(usernames[i],
    //               usrs["users"][i]["username"].get<std::string>());
    //     ASSERT_EQ(userPasswords[i],
    //               usrs["users"][i]["password"].get<std::string>());
    // }
}

TEST(update_desk, lessFieldsTest) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();
    json desk = {{"id", 1}, {"session_id", 3}};
    json resp = cl.updateDesk(desk);
    ASSERT_EQ(resp["status"], "ok");
}