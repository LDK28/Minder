#include <string>
#include <memory>
#include <pqxx/pqxx>

#include "DatabaseClient.h"

struct PostgreSQLConnectParams {
    std::string user;
    std::string password;
    std::string addr;
    std::string port;
    std::string dbName;
    std::string parameters;
};

class PostgreDatabaseClient : public DatabaseClient {
 private:
    PostgreSQLConnectParams connectParams;
    std::shared_ptr<pqxx::connection> con;

 public:
    PostgreDatabaseClient();
    json createTable(json) override;
    json dropTable(std::string) override;
    json update(json) override;
    json insert(json) override;
    json select(json) override;
    json remove(json) override;
    json query(std::string queryString);
};
