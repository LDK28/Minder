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
        strParams += "password = " + password + " ";

    if (!password.empty())
        strParams += "host = " + host + " ";
    std::cout << strParams;
    return strParams;
}

MySQLDatabaseClient::MySQLDatabaseClient(
    std::shared_ptr<MySQLConnectParams> conParams)
    : connectParams(conParams)
{
    driver = get_driver_instance();
    con = driver->connect("/var/run/mysqld/mysqld.sock", "ldk", "pass281001");
    con->setSchema("minder_db");

    if (con->isClosed())
    {
        std::cout << "Can't open database" << std::endl;
    }
    else
    {
        std::cout << "Opened database successfully: " << con->getSchema()
                  << std::endl;
    }
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
        stmt = con->createStatement();
        stmt->executeQuery(sql);
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
        stmt = con->createStatement();
        stmt->executeQuery(sql);
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
        stmt = con->createStatement();
        stmt->executeQuery(sql);
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

        stmt = con->createStatement();
        stmt->executeQuery(sql);

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
        stmt = con->createStatement();
        res = stmt->executeQuery(sql);
        response["rows"] = {};
        
        while (res->next())
        {
            json tmpRow;
            for (int i = 0; i < res->getMetaData()->getColumnCount(); i++)
            {
                tmpRow.push_back(res->getString(i));
            }
            response["rows"].push_back(tmpRow);
        }

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
        stmt = con->createStatement();
        stmt->executeQuery(sql);
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
        stmt = con->createStatement();
        res = stmt->executeQuery(queryString);

        while (res->next())
        {
            json tmpRow;
            for (int i = 0; i < res->getMetaData()->getColumnCount(); i++)
            {
                tmpRow.push_back(res->getString(i));
            }
            response["rows"].push_back(tmpRow);
        }
    }
    catch (std::exception &e)
    {
        response[STATUS_FIELD] = ERROR_STATUS;
        response["msg"] = e.what();
    }

    return response;
}