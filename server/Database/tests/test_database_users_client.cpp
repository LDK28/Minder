#include <gtest/gtest.h>

#include "json.hpp"

using json = nlohmann::json;

#include "DatabaseUsersClient.h"

const std::string sessionsTableName = "sessions";

std::vector<std::string> sessionsTableFields = {"name", "password"};

std::vector<std::string> sessionsnames = {"sess1", "sess2", "sess3", "sess4",
                                          "sess5"};
std::vector<std::string> sessionsPasswords = {"123", "123", "123", "123",
                                              "123"};

std::vector<int> sessionsSessionsIds = {1, 1, 2, 2, 3};

const std::string usrTableName = "users";

std::vector<std::string> userTableFields = {"username", "password",
                                            "session_id"};

std::vector<std::string> usernames = {"dima", "valera", "vika", "dasha",
                                      "polina"};
std::vector<std::string> userPasswords = {
    "dima_pass", "valera_pass", "vika_pass", "dasha_pass", "polina_pass"};

std::vector<int> userSessionsIds = {1, 1, 2, 2, 3};

class TestEnvironment : public ::testing::Environment {
 public:
    static std::shared_ptr<PostgreDatabaseClient> getPgClient() {
        static std::shared_ptr<PostgreSQLConnectParams> conParams =
            std::make_shared<PostgreSQLConnectParams>("p1xel", "db_minder");

        static std::shared_ptr<PostgreDatabaseClient> pg =
            std::make_shared<PostgreDatabaseClient>(conParams);

        return pg;
    }
    static DatabaseUsersClient getClient() {
        static std::shared_ptr<DatabaseClient> pg = getPgClient();
        static DatabaseUsersClient cl(pg);
        return cl;
    }

    static void fillSessionTable() {
        std::string query = "INSERT INTO " + sessionsTableName + " (";
        for (int i = 0; i < sessionsTableFields.size(); ++i) {
            query += sessionsTableFields[i];

            if (i != sessionsTableFields.size() - 1) {
                query += ", ";
            }
        }

        query += ")\n";

        query += "VALUES ";

        for (int i = 0; i < sessionsnames.size(); ++i) {
            query += "(";
            query += "\'" + sessionsnames[i] + "\',";
            query += sessionsPasswords[i];
            query += ")";

            if (i != sessionsnames.size() - 1) {
                query += ", ";
            }
        }

        query += ";";

        std::shared_ptr<DatabaseClient> pg = getPgClient();

        // std::cout << query;
        json req = pg->query(query);
        // std::cout << req.dump(5);
    }

    static void fillUsersTable() {
        std::string query = "INSERT INTO " + usrTableName + " (";
        for (int i = 0; i < userTableFields.size(); ++i) {
            query += userTableFields[i];

            if (i != userTableFields.size() - 1) {
                query += ", ";
            }
        }

        query += ")\n";

        query += "VALUES ";

        for (int i = 0; i < usernames.size(); ++i) {
            query += "(";
            query += "\'" + usernames[i] + "\',";
            query += "\'" + userPasswords[i] + "\',";
            query += std::to_string(userSessionsIds[i]);
            query += ")";

            if (i != usernames.size() - 1) {
                query += ", ";
            }
        }

        query += ";";

        std::shared_ptr<DatabaseClient> pg = getPgClient();

        pg->query(query);
    }

    static void copy_table(std::string tableName, std::string copyName) {
        std::string queryCreate =
            "CREATE TABLE" + copyName + "(LIKE" + tableName + "INCLUDING ALL);";
        std::string queryCopy =
            "INSERT INTO" + copyName + "TABLE" + tableName + ";";

        std::shared_ptr<DatabaseClient> pg =
            std::make_shared<PostgreDatabaseClient>();

        pg->query(queryCreate);
        pg->query(queryCopy);
    }

    // Initialise the timestamp.
    virtual void SetUp() {
        getPgClient();
        getClient();
        fillSessionTable();
        fillUsersTable();
    }
};

TEST(get_user_info, simpletest) {
    DatabaseUsersClient cl = TestEnvironment::getClient();
    int id = 1;
    json usr = cl.getUserInfo(id);
    // std::cout << usr << std::endl;
    ASSERT_EQ(usernames[0], usr["users"][0]["username"].get<std::string>());
    ASSERT_EQ(userPasswords[0], usr["users"][0]["password"].get<std::string>());
}

TEST(get_user_info_by_name, simpletest) {
    DatabaseUsersClient cl = TestEnvironment::getClient();
    std::string name = usernames[0];
    json usr = cl.getUserByName(name);
    // std::cout << usr << std::endl;
    ASSERT_EQ(usernames[0], usr["users"][0]["username"].get<std::string>());
    ASSERT_EQ(userPasswords[0], usr["users"][0]["password"].get<std::string>());
}

TEST(create_user, simpleCreate) {
    DatabaseUsersClient cl = TestEnvironment::getClient();
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
    DatabaseUsersClient cl = TestEnvironment::getClient();
    json req = {{"username", "fail"}, {"password", "test"}};
    json resp1 = cl.createUser(req);
    json resp2 = cl.createUser(req);
    ASSERT_EQ(resp2["status"], "error");
}

TEST(get_all_users_info, simpletest) {
    DatabaseUsersClient cl = TestEnvironment::getClient();
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
    DatabaseUsersClient cl = TestEnvironment::getClient();
    ASSERT_TRUE(cl.checkUser(usernames[0]));
}

TEST(check_user, testDontExist) {
    DatabaseUsersClient cl = TestEnvironment::getClient();
    ASSERT_FALSE(cl.checkUser("Uliana"));
}

TEST(get_users_in_session, testBasic) {
    DatabaseUsersClient cl = TestEnvironment::getClient();

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
    DatabaseUsersClient cl = TestEnvironment::getClient();

    std::vector<int> usersIds = {1, 2, 3};
    int sessionId = 3;
    json usrs = cl.addUsersInSession(usersIds, sessionId);
    ASSERT_EQ(usrs["status"], "ok");
}

TEST(update_user, simpleTest) {
    DatabaseUsersClient cl = TestEnvironment::getClient();

    json user = {
        {"id", 2}, {"username", "valera12312341"}, {"password", "1234"}};
    json resp = cl.updateUser(user);
    ASSERT_EQ(resp["status"], "ok");
}

TEST(update_user, lessFieldsTest) {
    DatabaseUsersClient cl = TestEnvironment::getClient();

    json user = {{"id", 2}, {"username", "varela123"}};
    json resp = cl.updateUser(user);
    ASSERT_EQ(resp["status"], "ok");
}

TEST(delete_user_by_id, simpleTest) {
    DatabaseUsersClient cl = TestEnvironment::getClient();

    int userId = 2;
    json resp = cl.deleteUsersById(userId);
    ASSERT_EQ(resp["status"], "ok");
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}