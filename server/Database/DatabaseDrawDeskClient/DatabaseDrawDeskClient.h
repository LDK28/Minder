#pragma once
#include "DatabaseClient.h"

class DatabaseDrawDeskClient {
 private:
    std::shared_ptr<DatabaseClient> client;

 public:
    DatabaseDrawDeskClient(std::shared_ptr<DatabaseClient> cl);
    json createDesk(const json &) const;
    json getDeskInfo(int deskId) const;
    json updateDesk(const json &) const;
    json getBlocksInfoFromDesk(int deskId) const;
    json addBlock(int deskId, const json &block);
    json updateBlock(const json &block);
    json deleteBlock(int blockId);
};
