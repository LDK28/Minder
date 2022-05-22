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

// blocks
const std::string blocksTableName = "blocks";
std::vector<std::string> blocksTableFields = {"parent_id",
                                              "x",
                                              "y",
                                              "txt",
                                              "desk_id",
                                              "color_text",
                                              "color_background",
                                              "color_border",
                                              "font"};
std::vector<int> blocksParentIds = {0, 0, 1, 1, 2};
std::vector<int> blocksX = {20, 30, 40, 50, 60};
std::vector<int> blocksY = {20, 30, 40, 50, 60};
std::vector<std::string> blocksTxt = {"dima", "valera", "vika", "dasha",
                                      "polina"};
std::vector<int> blocksDeskIds = {1, 1, 2, 2, 3};
const int countblocks = blocksDeskIds.size();

json BLOCKS_ENV = {{{"parent_id", 0},
                {"x", 20},
                {"y", 20},
                {"txt", "dima"},
                {"desk_id", 1},
                {"color_text", "#69a832"},
                {"color_background", "#69a832"},
                {"color_border", "#69a832"},
                {"font", "Arial"}},

               {{"parent_id", 0},
                {"x", 30},
                {"y", 30},
                {"txt", "valera"},
                {"desk_id", 1},
                {"color_text", "#69a832"},
                {"color_background", "#69a832"},
                {"color_border", "#69a832"},
                {"font", "Arial"}},

               {{"parent_id", 1},
                {"x", 40},
                {"y", 40},
                {"txt", "vika"},
                {"desk_id", 2},
                {"color_text", "#69a832"},
                {"color_background", "#69a832"},
                {"color_border", "#69a832"},
                {"font", "Arial"}},

               {{"parent_id", 1},
                {"x", 50},
                {"y", 50},
                {"txt", "dasha"},
                {"desk_id", 2},
                {"color_text", "#69a832"},
                {"color_background", "#69a832"},
                {"color_border", "#69a832"},
                {"font", "Arial"}},

               {{"parent_id", 2},
                {"x", 60},
                {"y", 60},
                {"txt", "polina"},
                {"desk_id", 3},
                {"color_text", "#69a832"},
                {"color_background", "#69a832"},
                {"color_border", "#69a832"},
                {"font", "Arial"}}

};

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

    static void fillDrawDesksTable() {
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

    static void fillBlocksTable() {
        std::string query = "INSERT INTO " + blocksTableName + " (";
        for (int i = 0; i < blocksTableFields.size(); ++i) {
            query += blocksTableFields[i];

            if (i != blocksTableFields.size() - 1) {
                query += ", ";
            }
        }

        query += ")\n";

        query += "VALUES ";
        for (int i = 0; i < BLOCKS_ENV.size(); ++i) {
            query += "(";
            for (int j = 0; j < blocksTableFields.size(); ++j) {
                auto field = blocksTableFields[j];
                // std::cout << field << " --- " << blocks[i][field] << std::endl;
                if (BLOCKS_ENV[i][field].is_string()) {
                    // std::cout << ">>>" << blocks[i][field].get<std::string>() << std::endl;
                    query += "\'" + BLOCKS_ENV[i][field].get<std::string>() + "\'";
                }

                if (BLOCKS_ENV[i][field].is_number()) {
                    query += std::to_string(BLOCKS_ENV[i][field].get<int>());
                }

                if (j != blocksTableFields.size() - 1) {
                    query += ", ";
                }
            }
            query += ")";

            if (i != BLOCKS_ENV.size() - 1) {
                query += ", ";
            }
        }

        query += ";";
        // std::cout << query << std::endl;
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
        getDesksClient();
        fillSessionTable();
        fillUsersTable();
        fillDrawDesksTable();
        fillBlocksTable();
    }
};