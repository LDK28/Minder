#pragma once
#include "DatabaseClient.h"

class DatabaseDrawDeskClient {
 private:
    std::shared_ptr<DatabaseClient> client;

 public:
    DatabaseDrawDeskClient(std::shared_ptr<DatabaseClient> cl);
    json createDesk(json) const;
    json getDeskInfo(int deskId) const;
    json updateDesk(json) const;
    json getBlocksInfoFromDesk(int deskId) const;
};
