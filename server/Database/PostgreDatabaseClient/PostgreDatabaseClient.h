#include <memory>
#include <pqxx/pqxx>
#include <string>

#include "DatabaseClient.h"

struct PostgreSQLConnectParams {
    std::string user;
    std::string password;
    std::string host;
    std::string dbName;

    PostgreSQLConnectParams(std::string user, std::string dbName,
                            std::string password = "", std::string host = "");

    std::string paramsToString() const;
};

class PostgreDatabaseClient : public DatabaseClient {
 private:
    std::shared_ptr<PostgreSQLConnectParams> connectParams;
    std::shared_ptr<pqxx::connection> con;

 public:
    PostgreDatabaseClient() = default;
    PostgreDatabaseClient(std::shared_ptr<PostgreSQLConnectParams> conParams);
    json createTable(json) override;
    json dropTable(std::string) override;
    json update(json) override;
    json insert(json) override;
    json select(json) override;
    json remove(json) override;
    json query(std::string queryString);
};
