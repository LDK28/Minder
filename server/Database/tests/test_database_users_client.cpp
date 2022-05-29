#include <gtest/gtest.h>

#include "DatabaseUsersClient.h"

#include "env_settings.hpp"

TEST(get_user_info, simpletest) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();
    int id = 1;
    json usr = cl.getUserInfo(id);
    // std::cout << usr << std::endl;
    ASSERT_EQ(usernames[0], usr["users"][0]["username"].get<std::string>());
    ASSERT_EQ(userPasswords[0], usr["users"][0]["password"].get<std::string>());
}

TEST(get_user_info_by_name, simpletest) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();
    std::string name = usernames[0];
    json usr = cl.getUserByName(name);
    // std::cout << usr << std::endl;
    ASSERT_EQ(usernames[0], usr["users"][0]["username"].get<std::string>());
    ASSERT_EQ(userPasswords[0], usr["users"][0]["password"].get<std::string>());
}

TEST(create_user, simpleCreate) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();
    std::string copyName = usrTableName + "Copy";

    json req = {{"username", "aaaaaaaaaaaaabcdc"}, {"password", "12341234"}};
    json resp = cl.createUser(req);
    // std::cout << "test create " << resp.dump(2) << std::endl;
    int id = std::stoi(resp["id"].get<std::string>());
    json usr = cl.getUserInfo(id);
    ASSERT_EQ(req["username"], usr["users"][0]["username"]);
    ASSERT_EQ(req["password"], usr["users"][0]["password"]);
}

TEST(create_user, existCreate) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();
    json req = {{"username", "fail"}, {"password", "test"}};
    json resp1 = cl.createUser(req);
    json resp2 = cl.createUser(req);
    ASSERT_EQ(resp2["status"], "error");
}

TEST(get_all_users_info, simpletest) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();
    json usrs = cl.getAllUsersInfo();
    // std::cout << usrs.dump(2) << std::endl;

    for (int i = 0; i < usernames.size(); i++) {
        ASSERT_EQ(usernames[i],
                  usrs["users"][i]["username"].get<std::string>());
        ASSERT_EQ(userPasswords[i],
                  usrs["users"][i]["password"].get<std::string>());
    }
}

TEST(check_user, testBasic) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();
    ASSERT_TRUE(cl.checkUser(usernames[0]));
}

TEST(validate, testBasic) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();
    ASSERT_TRUE(cl.validateUser(usernames[0], userPasswords[0]));
}

TEST(check_user, testDontExist) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();
    ASSERT_FALSE(cl.checkUser("Uliana"));
}

TEST(get_users_in_session, testBasic) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();

    int sessionId = 1;
    json usrs = cl.getUsersInSession(sessionId);
    // std::cout << usrs.dump(2) << std::endl;

    for (auto it = usrs["users"].begin(); it != usrs["users"].end(); ++it) {
        std::string username = (*it)["username"].get<std::string>();
        auto findIter = find(usernames.begin(), usernames.end(), username);
        ASSERT_TRUE(findIter != usernames.end());
        int usrIndex = findIter - usernames.begin();
        ASSERT_EQ(sessionId, userSessionsIds[usrIndex]);
    }
}

TEST(add_users_in_session, testOneUser) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();

    std::vector<int> usersIds = {1, 2, 3};
    int sessionId = 3;
    json usrs = cl.addUsersInSession(usersIds, sessionId);
    ASSERT_EQ(usrs["status"], "ok");
}

TEST(delete_user_from_session, simplTest)
{
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();

    std::vector<int> usersIds = {1, 2, 3};
    int userId = 3;
    json resp = cl.deleteUserFromSession(userId);
    ASSERT_EQ(resp["status"], "ok");

    json usr = cl.getUserInfo(userId);
    ASSERT_EQ(usr["users"][0]["session_id"], "");
}
TEST(update_user, simpleTest) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();

    json user = {
        {"id", 2}, {"username", "valera12312341"}, {"password", "1234"}};
    json resp = cl.updateUser(user);
    ASSERT_EQ(resp["status"], "ok");
}

TEST(update_user, lessFieldsTest) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();

    json user = {{"id", 2}, {"username", "varela123"}};
    json resp = cl.updateUser(user);
    ASSERT_EQ(resp["status"], "ok");
}

TEST(delete_user_by_id, simpleTest) {
    DatabaseUsersClient cl = TestEnvironment::getUsersClient();

    int userId = 2;
    json resp = cl.deleteUsersById(userId);
    ASSERT_EQ(resp["status"], "ok");
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}