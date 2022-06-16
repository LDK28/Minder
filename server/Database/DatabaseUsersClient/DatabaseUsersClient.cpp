#include "DatabaseUsersClient.h"

#include <iostream>

const std::string userTable = "users";
const std::vector<std::string> userTableFields = {"username", "password",
                                                  "session_id"};
json sqlUserResponseToJson(const json &sqlResponse) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    response["users"] = {};
    for (const auto &el : sqlResponse["rows"]) {
        int id = std::stoi(el[0].get<std::string>());
        json tmpUser = {{"id", id},
                        {userTableFields[0], el[1]},   // username
                        {userTableFields[1], el[2]},   // password
                        {userTableFields[2], el[3]}};  // session_id
        response["users"].push_back(tmpUser);
    }

    return response;
}

DatabaseUsersClient::DatabaseUsersClient(std::shared_ptr<DatabaseClient> cl) {
    client = cl;
}

json DatabaseUsersClient::createUser(const json &userData) const {
    // std::cout << client;
    json request = {{"table_name", userTable}, {"columns", {}}, {"values", {}}};

    for (const auto &el : userData.items()) {
        request["columns"].push_back(el.key());
    }
    for (const auto &el : userData) {
        request["values"].push_back(el);
    }

    // std::cout << request.dump(4);

    json response = client->insert(request);
    return response;
}

bool DatabaseUsersClient::checkUser(const std::string &name) const {
    json request = {{"FROM", {userTable}},
                    {"SELECT", {"COUNT(id)"}},
                    {"condition", "username=\'" + name + "\'"}};
    json resp = client->select(request);
    return !(resp["rows"][0][0] == "0");
}

bool DatabaseUsersClient::validateUser(const std::string &name,
                                       const std::string &password) const {
    std::string condition = "username=\'" + name + "\'";
    condition += "password=\'" + password + "\'";

    json request = {{"FROM", {userTable}},
                    {"SELECT", {"COUNT(id)"}},
                    {"condition", condition}};
    json resp = client->select(request);
    return !(resp["rows"][0][0] == "0");
}

json DatabaseUsersClient::getAllUsersInfo() const {
    json request = {{"FROM", {userTable}}, {"SELECT", {"*"}}};
    json resp = client->select(request);

    if (resp[STATUS_FIELD] == SUCCESS_STATUS) {
        json newResponse = sqlUserResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseUsersClient::getUserInfo(int id) const {
    json request = {{"FROM", {userTable}},
                    {"SELECT", {"*"}},
                    {"condition", "id=" + std::to_string(id)}};
    json resp = client->select(request);
    if (resp[STATUS_FIELD] == SUCCESS_STATUS) {
        json newResponse = sqlUserResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseUsersClient::getUsersInSession(int sessionId) const {
    json request = {{"FROM", {userTable}},
                    {"SELECT", {"*"}},
                    {"condition", "session_id=" + std::to_string(sessionId)}};
    json resp = client->select(request);
    if (resp[STATUS_FIELD] == SUCCESS_STATUS) {
        json newResponse = sqlUserResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseUsersClient::getUserByName(const std::string &name) const {
    json request = {{"FROM", {userTable}},
                    {"SELECT", {"*"}},
                    {"condition", "username=\'" + name + "\'"}};
    json resp = client->select(request);

    if (resp[STATUS_FIELD] == SUCCESS_STATUS) {
        json newResponse = sqlUserResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseUsersClient::addUsersInSession(const std::vector<int> &userId,
                                            int sessionId) const {
    json resp = {{STATUS_FIELD, SUCCESS_STATUS}};
    for (const auto &el : userId) {  //
        json request = {{"id", el}, {"session_id", sessionId}};
        resp = updateUser(request);

        if (resp[STATUS_FIELD] != SUCCESS_STATUS) {
            return resp;
        }
    }

    return resp;
}

json DatabaseUsersClient::updateUser(const json &sessData) const {
    json request = {{"table_name", userTable},
                    {"SET", {}},
                    {"condition", "id=" + sessData["id"].dump()}};
    for (json::const_iterator it = sessData.begin(); it != sessData.end(); ++it) {
        std::string curSetValue = it.key() + "=";
        if (it->is_string()) {
            curSetValue += "\'" + it->get<std::string>() + "\'";
        } else {
            curSetValue += it->dump();
        }

        request["SET"].push_back(curSetValue);
    }

    // std::cout << request.dump(1) << std::endl;
    json resp = client->update(request);
    return resp;
}

json DatabaseUsersClient::deleteUsersById(int id) const {
    json request = {{"table_name", userTable},
                    {"condition", "id=" + std::to_string(id)}};

    json resp = client->remove(request);
    return resp;
}
