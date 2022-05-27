#include <gtest/gtest.h>

#include "json.hpp"

using json = nlohmann::json;

#include "DatabaseSessionClient.h"
#include "env_settings.hpp"

TEST(get_session_info, simpletest) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();
    int id = 1;
    json session = cl.getSessionInfo(id);
    // std::cout << session.dump(2) << std::endl;
    ASSERT_EQ(sessionsnames[0],
              session["sessions"][0]["name"].get<std::string>());
    ASSERT_EQ(sessionsPasswords[0],
              session["sessions"][0]["password"].get<std::string>());
}


TEST(check_connection_to_session, simpleTest) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();

    json resp = cl.checkConnectionToSession(1, "123");
    std::cout << resp.dump(2);
    ASSERT_TRUE(resp[STATUS_FIELD] == SUCCESS_STATUS);
}


TEST(create_session, simpleCreate) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();

    json req = {{"name", "sess_to"}, {"password", "1234"}};
    json resp = cl.createSession(req);
    int id = std::stoi(resp["id"].get<std::string>());
    json session = cl.getSessionInfo(id);
    ASSERT_EQ(req["name"], session["sessions"][0]["name"]);
    ASSERT_EQ(req["password"], session["sessions"][0]["password"]);
}

TEST(create_session, existCreate) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();
    json req = {{"name", "fail"}, {"password", "test"}};
    json resp1 = cl.createSession(req);
    json resp2 = cl.createSession(req);
    ASSERT_EQ(resp2["status"], "error");
}

TEST(check_session, testBasic) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();
    ASSERT_TRUE(cl.checkSession("sess1"));
}

TEST(check_session, testDontExist) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();
    ASSERT_FALSE(cl.checkSession("fail_sesssion"));
}

TEST(select_sessions_with_user, simple_test) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();
    
}


TEST(update_session, simpleTest) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();

    json session = {{"id", 2}, {"name", "good_sess"}, {"password", "1234"}};
    json resp = cl.updateSession(session);
    ASSERT_EQ(resp["status"], "ok");
}

TEST(update_session, lessFieldsTest) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();

    json session = {{"id", 2}, {"password", "123"}};
    json resp = cl.updateSession(session);
    ASSERT_EQ(resp["status"], "ok");
}


TEST(delete_session, simpleTest) {
    DatabaseSessionClient cl = TestEnvironment::getSessionClient();

    int sessId = 1;
    json resp = cl.deleteSession(sessId);
    ASSERT_EQ(resp["status"], "ok");
    json sess = cl.getSessionInfo(sessId);
    ASSERT_TRUE(sess["sessions"].empty());
}



int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new TestEnvironment);
    return RUN_ALL_TESTS();
}