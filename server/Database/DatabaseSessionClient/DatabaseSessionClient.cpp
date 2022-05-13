#include "DatabaseSessionClient.h"

#include <iostream>

json sqlSessionResponseToJson(json sqlResponse) {
    json response = {{"status", "ok"}};
    response["sessions"] = {};
    for (auto &el : sqlResponse["rows"]) {
        json tmpSession = {{"id", el[0]},
                           {"name", el[1]},
                           {"password", el[2]},
                           {"desk_id", el[3]}};
        response["sessions"].push_back(tmpSession);
    }

    return response;
}

DatabaseSessionClient::DatabaseSessionClient(std::shared_ptr<DatabaseClient> cl) {
    client = cl;
}

json DatabaseSessionClient::createSession(json data) const {
    json request = {
        {"table_name", "sessions"},
        {"columns", {"name", "password", "desk_id"}},
        {"values", {data["name"], data["password"], data["desk_id"]}}};

    // std::cout << request.dump(2) << std::endl;
    json response = client->insert(request);
    return response;
}

bool DatabaseSessionClient::checkSession(std::string name) const {
    json request = {{"FROM", {"sessions"}},
                    {"SELECT", {"COUNT(id)"}},
                    {"condition", "name=\'" + name + "\'"}};
    json resp = client->select(request);
    return !(resp["rows"][0][0] == "0");
}

json DatabaseSessionClient::updateSession(json sessData) const {
    json request = {{"table_name", "sessions"},
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

    std::cout << request.dump(1) << std::endl;
    json resp = client->update(request);
    return resp;
}
json DatabaseSessionClient::getSessionInfo(int id) const {
    json request = {{"FROM", {"sessions"}},
                    {"SELECT", {"*"}},
                    {"condition", "id=" + std::to_string(id)}};
    json resp = client->select(request);
    if (resp["status"] == "ok") {
        json newResponse = sqlSessionResponseToJson(resp);
        std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}
json DatabaseSessionClient::selectSessionsWithUser(int userId) const {
    json request = {{"FROM", {"sessions", "users"}},
                    {"SELECT", {"sessions.*"}},
                    {"condition", "users.id=" + std::to_string(userId) +
                                      " and sessions.id = users.session_id"}};
    std::cout << request.dump(1) << std::endl;

    json resp = client->select(request);
    if (resp["status"] == "ok") {
        json newResponse = sqlSessionResponseToJson(resp);
        std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseSessionClient::deleteSession(int id) const {
    json request = {{"table_name", "sessions"},
                    {"condition", "id=" + std::to_string(id)}};

    json resp = client->remove(request);

    return resp;
}