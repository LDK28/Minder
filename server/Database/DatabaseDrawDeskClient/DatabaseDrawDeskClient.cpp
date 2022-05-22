#include "DatabaseDrawDeskClient.h"

const std::string BLOCKS_TABLE = "blocks";
const std::string DESK_TABLE = "draw_desks";

static const std::vector<std::string> blocksTableFields = {"parent_id",
                                                           "x",
                                                           "y",
                                                           "txt",
                                                           "desk_id",
                                                           "color_text",
                                                           "color_background",
                                                           "color_border",
                                                           "font"};

static const std::vector<std::string> drawDeskTableFields = {"session_id"};

DatabaseDrawDeskClient::DatabaseDrawDeskClient(
    std::shared_ptr<DatabaseClient> cl) {
    client = cl;
}

bool is_number(const std::string &s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

json sqlDeskResponseToJson(const json &sqlResponse) {
    json response = {{STATUS_FIELD, SUCCESS_STATUS}};
    response["desks"] = {};
    for (auto &el : sqlResponse["rows"]) {
        int id = std::stoi(el[0].get<std::string>());
        json tmpDesk = {{"id", id},
                        {"session_id", std::stoi(el[1].get<std::string>())}};
        response["desks"].push_back(tmpDesk);
    }

    return response;
}

json sqlBlocksResponseToJson(const json &sqlResponse) {
    json response = {{STATUS_FIELD, "ok"}};
    response[BLOCKS_TABLE] = {};
    for (const auto &el : sqlResponse["rows"]) {
        int id = std::stoi(el[0].get<std::string>());
        json tmpUser = {{"id", id}};
        for (int j = 0; j < blocksTableFields.size(); ++j) {
            if (is_number(el[j + 1])) {
                tmpUser[blocksTableFields[j]] =
                    std::stoi(el[j + 1].get<std::string>());
            } else {
                tmpUser[blocksTableFields[j]] = el[j + 1];
            }
        }
        response[BLOCKS_TABLE].push_back(tmpUser);
    }

    return response;
}

json DatabaseDrawDeskClient::createDesk(const json &deskData) const {
    json request = {
        {"table_name", DESK_TABLE}, {"columns", {}}, {"values", {}}};

    for (const auto &el : deskData.items()) {
        request["columns"].push_back(el.key());
    }
    for (const auto &el : deskData) {
        request["values"].push_back(el);
    }

    // std::cout << request.dump(4);

    json response = client->insert(request);
    return response;
}
json DatabaseDrawDeskClient::getDeskInfo(int deskId) const {
    json request = {{"FROM", {DESK_TABLE}},
                    {"SELECT", {"*"}},
                    {"condition", "id=" + std::to_string(deskId)}};

    json resp = client->select(request);
    if (resp[STATUS_FIELD] == SUCCESS_STATUS) {
        json newResponse = sqlDeskResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}
json DatabaseDrawDeskClient::updateDesk(const json &deskData) const {
    json request = {{"table_name", DESK_TABLE},
                    {"SET", {}},
                    {"condition", "id=" + deskData["id"].dump()}};
    for (json::const_iterator it = deskData.begin(); it != deskData.end();
         ++it) {
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
    json request = {{"FROM", {BLOCKS_TABLE}},
                    {"SELECT", {"*"}},
                    {"condition", "desk_id=" + std::to_string(deskId)}};
    json resp = client->select(request);
    if (resp[STATUS_FIELD] == SUCCESS_STATUS) {
        json newResponse = sqlBlocksResponseToJson(resp);
        // std::cout << newResponse.dump(2) << std::endl;
        return newResponse;
    } else {
        return resp;
    }
}

json DatabaseDrawDeskClient::addBlock(int deskId, const json &block) {
    json request = {
        {"table_name", BLOCKS_TABLE}, {"columns", {}}, {"values", {}}};

    for (const auto &el : block.items()) {
        request["columns"].push_back(el.key());
    }
    for (const auto &el : block) {
        request["values"].push_back(el);
    }

    // std::cout << request.dump(4);

    json response = client->insert(request);
    return response;
}

json DatabaseDrawDeskClient::updateBlock(const json &block) {
    json request = {{"table_name", BLOCKS_TABLE},
                    {"SET", {}},
                    {"condition", "id=" + block["id"].dump()}};
    for (json::const_iterator it = block.begin(); it != block.end(); ++it) {
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

json DatabaseDrawDeskClient::deleteBlock(int blockId) {
    json request = {{"table_name", BLOCKS_TABLE},
                    {"condition", "id=" + std::to_string(blockId)}};

    json resp = client->remove(request);

    return resp;
}