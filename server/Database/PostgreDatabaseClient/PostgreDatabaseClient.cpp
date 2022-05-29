#include "PostgreDatabaseClient.h"

#include <boost/format.hpp>
#include <iostream>

PostgreSQLConnectParams::PostgreSQLConnectParams(std::string user,
                                                 std::string dbName,
                                                 std::string password,
                                                 std::string host)
    : user(user), password(password), host(host), dbName(dbName) {}

std::string PostgreSQLConnectParams::paramsToString() const {
    std::string strParams = "dbname = " + dbName + " ";
    strParams += "user = " + user + " ";

    if (!password.empty()) {
        strParams += "password = " + password + " ";
    }

    if (!password.empty()) {
        strParams += "host = " + host + " ";
    }
    std::cout << strParams;
    return strParams;
}

PostgreDatabaseClient::PostgreDatabaseClient(
    std::shared_ptr<PostgreSQLConnectParams> conParams)
    : connectParams(conParams) {
    con = std::make_shared<pqxx::connection>(connectParams->paramsToString());
    // con = std::make_shared<pqxx::connection>("dbname = db_minder user = postgres");

    if ((*con).is_open()) {
        std::cout << "Opened database successfully: " << (*con).dbname()
                  << std::endl;
    } else {
        std::cout << "Can't open database" << std::endl;
    }
}

json PostgreDatabaseClient::createTable(json req) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string sql = boost::str(boost::format("CREATE TABLE %1% (") %
                                 req["name"].get<std::string>());
    for (int i = 0; i < req["columns"].size(); i++) {
        sql += req["columns"][i].get<std::string>();

        if (i != req["columns"].size() - 1) {
            sql += ",";
        }
    }
    sql += ");";

    try {
        pqxx::work worker(*con);

        worker.exec(sql.c_str());
        worker.commit();
    } catch (std::exception &e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}
json PostgreDatabaseClient::dropTable(std::string tableName) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    try {
        std::string sql = "DROP TABLE " + tableName + ";";
        pqxx::work worker(*con);

        worker.exec(sql.c_str());
        worker.commit();
    } catch (std::exception &e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}
json PostgreDatabaseClient::update(json req) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string sql = boost::str(boost::format("UPDATE %1% ") %
                                 req["table_name"].get<std::string>());
    sql += "SET ";
    for (int i = 0; i < req["SET"].size(); i++) {
        sql += req["SET"][i].get<std::string>();

        if (i != req["SET"].size() - 1) {
            sql += ",";
        }
    }

    if (!req["condition"].empty()) {
        sql += " WHERE " + req["condition"].get<std::string>();
    }
    sql += ";";

    try {
        pqxx::work worker(*con);
        worker.exec(sql.c_str());
        worker.commit();
    } catch (std::exception &e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    // std::cout << sql << std::endl;
    return response;
}

json PostgreDatabaseClient::insert(json req) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    // std::cout << req.dump(2);
    std::string sql = boost::str(boost::format("INSERT INTO %1% (") %
                                 req["table_name"].get<std::string>());

    for (int i = 0; i < req["columns"].size(); i++) {
        if (req["columns"][i].is_null()) {
            continue;
        }
        sql += req["columns"][i].get<std::string>();

        if (i != req["columns"].size() - 1) {
            sql += ",";
        }
    }

    sql += ")\n VALUES (";

    for (int i = 0; i < req["values"].size(); i++) {
        if (req["values"][i].is_null()) {
            continue;
        }

        if (req["values"][i].is_string()) {
            sql += "\'" + req["values"][i].get<std::string>() + "\'";
        } else {
            sql += "\'" + req["values"][i].dump() + "\'";
        }

        if (i != req["values"].size() - 1 && !req["values"][i + 1].is_null()) {
            sql += ", ";
        }
    }
    sql += ");";

    // std::cout << sql << std::endl;

    try {
        pqxx::work worker(*con);

        worker.exec(sql.c_str());
        worker.commit();
        json resp_query =
            query(std::string("SELECT currval(pg_get_serial_sequence(") + "\'" +
                  req["table_name"].get<std::string>() + "\'" + ", \'id\'));");
        worker.commit();

        if (resp_query[STATUS_FIELD] == SUCCESS_STATUS)
            response["id"] = resp_query["rows"][0][0];
        else {
            response = resp_query;
        }
        // std::cout << "val" << resp.dump(4);
    } catch (std::exception &e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}

json PostgreDatabaseClient::select(json req) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string sql = "SELECT ";
    for (int i = 0; i < req["SELECT"].size(); i++) {
        sql += req["SELECT"][i].get<std::string>();

        if (i != req["SELECT"].size() - 1) {
            sql += ",";
        }
    }
    sql += "\n FROM ";
    for (int i = 0; i < req["FROM"].size(); i++) {
        sql += req["FROM"][i].get<std::string>();

        if (i != req["FROM"].size() - 1) {
            sql += ",";
        }
    }

    if (!req["condition"].empty()) {
        sql += " WHERE " + req["condition"].get<std::string>();
    }
    sql += ";";
    // std::cout << sql << std::endl;

    try {
        pqxx::work worker(*con);

        pqxx::result r = worker.exec(sql.c_str());
        worker.commit();
        response["rows"] = {};

        for (pqxx::result::const_iterator row = r.begin(); row != r.end();
             ++row) {
            json tmpRow;
            for (pqxx::row::const_iterator field = row->begin();
                 field != row->end(); ++field) {
                tmpRow.push_back(field.c_str());
            }
            response["rows"].push_back(tmpRow);
        }
        // std::cout << response.dump(4) << std::endl;

    } catch (std::exception &e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}
json PostgreDatabaseClient::remove(json req) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string sql = "DELETE FROM " + req["table_name"].get<std::string>();
    if (!req["condition"].empty()) {
        sql += " WHERE " + req["condition"].get<std::string>();
    }
    sql += ";";
    // std::cout << sql;
    try {
        pqxx::work worker(*con);

        worker.exec(sql.c_str());
        worker.commit();
    } catch (std::exception &e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}

json PostgreDatabaseClient::query(std::string queryString) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    try {
        pqxx::work worker(*con);

        pqxx::result r = worker.exec(queryString.c_str());
        for (pqxx::result::const_iterator row = r.begin(); row != r.end();
             ++row) {
            json tmpRow;
            for (pqxx::row::const_iterator field = row->begin();
                 field != row->end(); ++field) {
                tmpRow.push_back(field.c_str());
            }
            response["rows"].push_back(tmpRow);
        }
        // std::cout << response.dump(4) << std::endl;
        worker.commit();
    } catch (std::exception &e) {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}