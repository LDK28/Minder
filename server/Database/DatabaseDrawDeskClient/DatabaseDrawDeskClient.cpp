#include "DatabaseDrawDeskClient.h"

DatabaseDrawDeskClient::DatabaseDrawDeskClient(
    std::shared_ptr<DatabaseClient> cl) {
    client = cl;
}

json DatabaseDrawDeskClient::getDeskData(int deskId) const { return json{{}}; }
json DatabaseDrawDeskClient::updateDeskData(json) const { return json{{}}; }
json DatabaseDrawDeskClient::getBlocksFromDesk(int deskId) const {
    return json{{}};
}
