#include <gtest/gtest.h>

#include "DatabaseDrawDeskClient.h"
#include "DatabaseSessionClient.h"
#include "DatabaseUsersClient.h"
#include "PostgreDatabaseClient.h"
#include "json.hpp"

using json = nlohmann::json;

// sessions
const std::string sessionsTableName = "sessions";

std::vector<std::string> sessionsTableFields = {"name", "password"};
std::vector<std::string> sessionsnames = {"sess1", "sess2", "sess3", "sess4",
                                          "sess5"};
std::vector<std::string> sessionsPasswords = {"123", "123", "123", "123",
                                              "123"};

// users
const std::string usrTableName = "users";

std::vector<std::string> userTableFields = {"username", "password",
                                            "session_id"};
std::vector<std::string> usernames = {"dima", "valera", "vika", "dasha",
                                      "polina"};
std::vector<std::string> userPasswords = {
    "dima_pass", "valera_pass", "vika_pass", "dasha_pass", "polina_pass"};
std::vector<int> userSessionsIds = {1, 1, 2, 2, 3};

// draw desks
const std::string drawDesksTableName = "draw_desks";
std::vector<std::string> deskTableFields = {"session_id"};
std::vector<int> deskSessionIds = {1, 1, 2, 2, 3};
const int countDesks = deskSessionIds.size();

class TestEnvironment : public ::testing::Environment {
 public:
    static std::shared_ptr<PostgreDatabaseClient> getPgClient() {
        static std::shared_ptr<PostgreSQLConnectParams> conParams =
            std::make_shared<PostgreSQLConnectParams>("p1xel", "db_minder");

        static std::shared_ptr<PostgreDatabaseClient> pg =
            std::make_shared<PostgreDatabaseClient>(conParams);

        return pg;
    }
    static DatabaseUsersClient getUsersClient() {
        static std::shared_ptr<DatabaseClient> pg = getPgClient();
        static DatabaseUsersClient cl(pg);
        return cl;
    }

    static DatabaseDrawDeskClient getDesksClient() {
        static std::shared_ptr<DatabaseClient> pg = getPgClient();
        static DatabaseDrawDeskClient cl(pg);
        return cl;
    }

    static DatabaseSessionClient getSessionClient() {
        static std::shared_ptr<DatabaseClient> pg = getPgClient();
        static DatabaseSessionClient cl(pg);
        return cl;
    }

    static void clearTables() {
        std::shared_ptr<DatabaseClient> pg = getPgClient();
        std::string query = "TRUNCATE users RESTART IDENTITY cascade;";
        pg->query(query);
        query = "TRUNCATE sessions RESTART IDENTITY cascade;";
        pg->query(query);
        query = "TRUNCATE draw_desks RESTART IDENTITY cascade;";
        pg->query(query);
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

    static void fillDrawDesks() {
        std::string query = "INSERT INTO " + drawDesksTableName + " (";
        for (int i = 0; i < deskTableFields.size(); ++i) {
            query += deskTableFields[i];

            if (i != deskTableFields.size() - 1) {
                query += ", ";
            }
        }

        query += ")\n";

        query += "VALUES ";

        for (int i = 0; i < countDesks; ++i) {
            query += "(";
            query += std::to_string(deskSessionIds[i]);
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
        clearTables();
        getPgClient();
        getUsersClient();
        fillSessionTable();
        fillUsersTable();
        fillDrawDesks();
    }
};