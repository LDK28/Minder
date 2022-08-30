#include <gtest/gtest.h>

#include "DatabaseDrawDeskClient.h"
#include "env_settings.hpp"

bool findBlockInEnv(json block) {
    block.erase("id");

    for (int i = 0; i < BLOCKS_ENV.size(); ++i) {
        if (BLOCKS_ENV[i] == block) {
            return true;
        }
    }

    return false;
}

bool findBlockInArr(json block, json blocksArr) {

    for (int i = 0; i < blocksArr.size(); ++i) {
        if (blocksArr[i] == block) {
            return true;
        }
    }

    return false;
}

TEST(get_desk_info, simpletest) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();
    int id = 1;
    json desk = cl.getDeskInfo(id);
    // std::cout << desk.dump(2) << std::endl;
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
    json blocksResp = cl.getBlocksInfoFromDesk(1);
    // std::cout << blocksResp.dump(2) << std::endl;

    for (int i = 0; i < blocksResp["blocks"].size(); ++i) {
        ASSERT_TRUE(findBlockInEnv(blocksResp["blocks"][i]));
    }
}

TEST(update_desk, lessFieldsTest) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();
    json desk = {{"id", 1}, {"session_id", 3}};
    json resp = cl.updateDesk(desk);
    // std::cout << resp.dump(2) << std::endl;
    ASSERT_EQ(resp["status"], "ok");
}

TEST(addblock, simpleTest) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();
    json block = {
        {"parent_id", 0},
        {"x", 20},
        {"y", 20},
        {"txt", "loool"},
        {"desk_id", 1},
        {"color_text", "#69a832"},
        {"color_background", "#69a832"},
        {"color_border", "#69a832"},
        {"font", "Arial"}
    };

    int deskId = 1;
    json resp = cl.addBlock(deskId, block);
    // std::cout << resp.dump(2);
    ASSERT_EQ(resp[STATUS_FIELD], SUCCESS_STATUS);
}

TEST(updateblock, simpleTest) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();
    json block = {
        {"id", 5},
        {"parent_id", 0},
        {"x", 20},
        {"y", 20},
        {"txt", "polinochka"},
        {"desk_id", 1},
        {"color_text", "#69a832"},
        {"color_background", "#69a832"},
        {"color_border", "#69a832"},
        {"font", "Arial"}
    };

    int deskId = 1;
    json resp = cl.updateBlock(block);
    // std::cout << resp.dump(2) << std::endl;
    ASSERT_EQ(resp[STATUS_FIELD], SUCCESS_STATUS);
    json blocksResp = cl.getBlocksInfoFromDesk(block["desk_id"].get<int>());
    ASSERT_TRUE(findBlockInArr(block, blocksResp["blocks"]));
}

TEST(delete_block, simpleTest) {
    DatabaseDrawDeskClient cl = TestEnvironment::getDesksClient();
    int blockId = 3;
    json resp = cl.deleteBlock(blockId);
    // std::cout << resp.dump(2) << std::endl;
    ASSERT_EQ(resp[STATUS_FIELD], SUCCESS_STATUS);
}



int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);

    return RUN_ALL_TESTS();
}