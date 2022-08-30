#pragma once

#include <memory>
#include <pqxx/pqxx>
#include <string>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "DatabaseClient.h"

struct MySQLConnectParams
{
    std::string user;
    std::string password;
    std::string host;
    std::string dbName;

    MySQLConnectParams(std::string user, std::string dbName,
                       std::string password = "", std::string host = "");

    std::string paramsToString() const;
};

class MySQLDatabaseClient : public DatabaseClient
{
private:
    std::shared_ptr<MySQLConnectParams> connectParams;

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;

public:
    MySQLDatabaseClient() = default;
    MySQLDatabaseClient(std::shared_ptr<MySQLConnectParams> conParams);
    json createTable(json) override;
    json dropTable(std::string) override;
    json update(json) override;
    json insert(json) override;
    json select(json) override;
    json remove(json) override;
    json query(std::string queryString);
};
