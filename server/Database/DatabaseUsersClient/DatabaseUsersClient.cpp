#include "DatabaseUsersClient.h"

#include <iostream>

static const std::vector<std::string> userTableFields = {"username", "password",
                                                         "session_id"};

json sqlUserResponseToJson(json sqlResponse) {
    json response = {{"status", "ok"}};
    response["users"] = {};
    for (auto &el : sqlResponse["rows"]) {
        int id = std::stoi(el[0].get<std::string>());
        json tmpUser = {{"id", id},
                        {"username", el[1]},
                        {"password", el[2]},
                        {"session_id", el[3]}};
        response["users"].push_back(tmpUser);
    }

    return response;
}

DatabaseUsersClient::DatabaseUsersClient(std::shared_ptr<DatabaseClient> cl) {
    client = cl;
}

json DatabaseUsersClient::createUser(json userData) const {
    // std::cout << client;
    json request = {{"table_name", "users"}, {"columns", {}}, {"values", {}}};

    for (auto &el : userData.items()) {
        request["columns"].push_back(el.key());
    }
    for (auto &el : userData) {
        request["values"].push_back(el);
    }

    // std::cout << request.dump(4);

    json response = client->insert(request);
    return response;
}

bool DatabaseUsersClient::checkUser(std::string name) const {
    json request = {{"FROM", {"users"}},
                    {"SELECT", {"COUNT(id)"}},
                    {"condition", "username=\'" + name + "\'"}};
    json resp = client->select(request);
    return !(resp["rows"][0][0] == "0");
}
json DatabaseUsersClient::getAllUsersInfo() const {
    json request = {{"FROM", {"users"}}, {"SELECT", {"*"}}};
    json resp = client->select(request);

    if (resp["status"] == "ok") {
        json newResponse = sqlUserResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}
json DatabaseUsersClient::getUserInfo(int id) const {
    json request = {{"FROM", {"users"}},
                    {"SELECT", {"*"}},
                    {"condition", "id=" + std::to_string(id)}};
    json resp = client->select(request);
    if (resp["status"] == "ok") {
        json newResponse = sqlUserResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseUsersClient::getUsersInSession(int sessionId) const {
    json request = {{"FROM", {"users"}},
                    {"SELECT", {"*"}},
                    {"condition", "session_id=" + std::to_string(sessionId)}};
    json resp = client->select(request);
    if (resp["status"] == "ok") {
        json newResponse = sqlUserResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseUsersClient::getUserByName(std::string name) const {
    json request = {{"FROM", {"users"}},
                    {"SELECT", {"*"}},
                    {"condition", "username=\'" + name + "\'"}};
    json resp = client->select(request);

    if (resp["status"] == "ok") {
        json newResponse = sqlUserResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseUsersClient::addUsersInSession(std::vector<int> userId,
                                            int sessionId) const {
    json resp = {{"status", "ok"}};
    for (auto &el : userId) {
        json request = {{"id", el}, {"session_id", sessionId}};
        resp = updateUser(request);

        if (resp["status"] != "ok") {
            return resp;
        }
    }
    return resp;
}

json DatabaseUsersClient::updateUser(json sessData) const {
    json request = {{"table_name", "users"},
                    {"SET", {}},
                    {"condition", "id=" + sessData["id"].dump()}};
    for (json::iterator it = sessData.begin(); it != sessData.end(); ++it) {
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
    json request = {{"table_name", "users"},
                    {"condition", "id=" + std::to_string(id)}};

    json resp = client->remove(request);
    return resp;
}
