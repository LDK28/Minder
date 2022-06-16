#include "MySQLDatabaseClient.h"

#include <boost/format.hpp>
#include <iostream>

MySQLConnectParams::MySQLConnectParams(std::string user,
                                       std::string dbName,
                                       std::string password,
                                       std::string host)
    : user(user), password(password), host(host), dbName(dbName) {}

std::string MySQLConnectParams::paramsToString() const
{
    std::string strParams = "dbname = " + dbName + " ";
    strParams += "user = " + user + " ";

    if (!password.empty())
    {
        strParams += "password = " + password + " ";
    }

    if (!password.empty())
    {
        strParams += "host = " + host + " ";
    }
    std::cout << strParams;
    return strParams;
}

MySQLDatabaseClient::MySQLDatabaseClient(
    std::shared_ptr<MySQLConnectParams> conParams)
    : connectParams(conParams)
{
    // con = std::make_shared<MYSQL>(connectParams->paramsToString());
    // con = std::make_shared<pqxx::connection>("dbname = db_minder user = postgres");

    con = mysql_init(NULL);

    if (con == NULL)
        std::cout << "Error: can'tcreate MySQL-descriptor\n";
    if (!mysql_real_connect(con, "localhost", "root", "root", "test", NULL, NULL, 0))
        std::cout << "Error: can'tconnecttodatabase\n";
    else
        std::cout << "Opened database successfully: \n"
                  << con->db << std::endl;
    ;
}

json MySQLDatabaseClient::createTable(json req)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string sql = boost::str(boost::format("CREATE TABLE %1% (") %
                                 req["name"].get<std::string>());
    for (int i = 0; i < req["columns"].size(); i++)
    {
        sql += req["columns"][i].get<std::string>();

        if (i != req["columns"].size() - 1)
        {
            sql += ",";
        }
    }
    sql += ");";

    try
    {
        mysql_query(con, sql.c_str());
        res = mysql_store_result(con);
        if (!res)
            throw "";
    }
    catch (std::exception &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}
json MySQLDatabaseClient::dropTable(std::string tableName)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    try
    {
        std::string sql = "DROP TABLE " + tableName + ";";
        mysql_query(con, sql.c_str());
    }
    catch (std::exception &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}
json MySQLDatabaseClient::update(json req)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string sql = boost::str(boost::format("UPDATE %1% ") %
                                 req["table_name"].get<std::string>());
    sql += "SET ";
    for (int i = 0; i < req["SET"].size(); i++)
    {
        sql += req["SET"][i].get<std::string>();

        if (i != req["SET"].size() - 1)
        {
            sql += ",";
        }
    }

    if (!req["condition"].empty())
    {
        sql += " WHERE " + req["condition"].get<std::string>();
    }
    sql += ";";

    try
    {
        mysql_query(con, sql.c_str());
    }
    catch (std::exception &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    // std::cout << sql << std::endl;
    return response;
}

///
json MySQLDatabaseClient::insert(json req)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    // std::cout << req.dump(2);
    std::string sql = boost::str(boost::format("INSERT INTO %1% (") %
                                 req["table_name"].get<std::string>());

    for (int i = 0; i < req["columns"].size(); i++)
    {
        if (req["columns"][i].is_null())
        {
            continue;
        }
        sql += req["columns"][i].get<std::string>();

        if (i != req["columns"].size() - 1)
        {
            sql += ",";
        }
    }

    sql += ")\n VALUES (";

    for (int i = 0; i < req["values"].size(); i++)
    {
        if (req["values"][i].is_null())
        {
            continue;
        }

        if (req["values"][i].is_string())
        {
            sql += "\'" + req["values"][i].get<std::string>() + "\'";
        }
        else
        {
            sql += "\'" + req["values"][i].dump() + "\'";
        }

        if (i != req["values"].size() - 1 && !req["values"][i + 1].is_null())
        {
            sql += ", ";
        }
    }
    sql += ");";

    try
    {

        mysql_query(con, sql.c_str());

        json resp_query =
            query(std::string("SELECT currval(pg_get_serial_sequence(") + "\'" +
                  req["table_name"].get<std::string>() + "\'" + ", \'id\'));");

        if (resp_query[STATUS_FIELD] == SUCCESS_STATUS)
            response["id"] = resp_query["rows"][0][0];
        else
        {
            response = resp_query;
        }
        // std::cout << "val" << resp.dump(4);
    }
    catch (std::exception &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}

json MySQLDatabaseClient::select(json req)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string sql = "SELECT ";
    for (int i = 0; i < req["SELECT"].size(); i++)
    {
        sql += req["SELECT"][i].get<std::string>();

        if (i != req["SELECT"].size() - 1)
        {
            sql += ",";
        }
    }
    sql += "\n FROM ";
    for (int i = 0; i < req["FROM"].size(); i++)
    {
        sql += req["FROM"][i].get<std::string>();

        if (i != req["FROM"].size() - 1)
        {
            sql += ",";
        }
    }

    if (!req["condition"].empty())
    {
        sql += " WHERE " + req["condition"].get<std::string>();
    }
    sql += ";";
    // std::cout << sql << std::endl;

    try
    {
        mysql_query(con, sql.c_str()); 

        if (res = mysql_store_result(con))
            while (row = mysql_fetch_row(res))
                for (int i = 0; i < mysql_num_fields(res); i++)
                {
                    json tmpRow = row[i];

                    response["rows"].push_back(tmpRow);
                }
        else
            throw;
    }
    catch (std::exception &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}

json MySQLDatabaseClient::remove(json req)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    std::string sql = "DELETE FROM " + req["table_name"].get<std::string>();
    if (!req["condition"].empty())
    {
        sql += " WHERE " + req["condition"].get<std::string>();
    }
    sql += ";";
    // std::cout << sql;
    try
    {
        mysql_query(con, sql.c_str());
    }
    catch (std::exception &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}

json MySQLDatabaseClient::query(std::string queryString)
{
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    try
    {
        mysql_query(con, queryString.c_str()); 

        if (res = mysql_store_result(con))
            while (row = mysql_fetch_row(res))
                for (int i = 0; i < mysql_num_fields(res); i++)
                {
                    json tmpRow = row[i];

                    response["rows"].push_back(tmpRow);
                }
        else
            throw;
    }
    catch (std::exception &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}