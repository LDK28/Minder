#include "DatabaseDrawDeskClient.h"

static const std::vector<std::string> blocksTableFields = {
    "parent_id", "x", "y", "txt", "desk_id"};

static const std::vector<std::string> drawDeskTableFields = {"session_id"};

DatabaseDrawDeskClient::DatabaseDrawDeskClient(
    std::shared_ptr<DatabaseClient> cl) {
    client = cl;
}

json sqlDeskResponseToJson(json sqlResponse) {
    json response = {{"status", "ok"}};
    response["desks"] = {};
    for (auto &el : sqlResponse["rows"]) {
        int id = std::stoi(el[0].get<std::string>());
        json tmpDesk = {{"id", id}, {"session_id", std::stoi(el[1].get<std::string>())}};
        response["desks"].push_back(tmpDesk);
    }

    return response;
}

json sqlBlocksResponseToJson(json sqlResponse) {
    json response = {{"status", "ok"}};
    response["blocks"] = {};
    for (auto &el : sqlResponse["rows"]) {
        int id = std::stoi(el[0].get<std::string>());
        json tmpUser = {{"id", id},
                        {blocksTableFields[0], el[1]},
                        {blocksTableFields[1], el[2]},
                        {blocksTableFields[2], el[3]},
                        {blocksTableFields[3], el[4]},
                        {blocksTableFields[4], el[5]}};
        response["blocks"].push_back(tmpUser);
    }

    return response;
}

json DatabaseDrawDeskClient::createDesk(json deskData) const {
    json request = {
        {"table_name", "draw_desks"}, {"columns", {}}, {"values", {}}};

    for (auto &el : deskData.items()) {
        request["columns"].push_back(el.key());
    }
    for (auto &el : deskData) {
        request["values"].push_back(el);
    }

    // std::cout << request.dump(4);

    json response = client->insert(request);
    return response;
}
json DatabaseDrawDeskClient::getDeskInfo(int deskId) const {
    json request = {{"FROM", {"draw_desks"}},
                    {"SELECT", {"*"}},
                    {"condition", "id=" + std::to_string(deskId)}};

    json resp = client->select(request);
    if (resp["status"] == "ok") {
        json newResponse = sqlDeskResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}
json DatabaseDrawDeskClient::updateDesk(json deskData) const {
    json request = {{"table_name", "draw_desks"},
                    {"SET", {}},
                    {"condition", "id=" + deskData["id"].dump()}};
    for (json::iterator it = deskData.begin(); it != deskData.end(); ++it) {
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
json DatabaseDrawDeskClient::getBlocksInfoFromDesk(int deskId) const {
    json request = {{"FROM", {"blocks"}},
                    {"SELECT", {"*"}},
                    {"condition", "deks_id=" + std::to_string(deskId)}};
    json resp = client->select(request);
    if (resp["status"] == "ok") {
        json newResponse = sqlBlocksResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}
