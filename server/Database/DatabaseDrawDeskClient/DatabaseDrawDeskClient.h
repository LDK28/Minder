#include "DatabaseClient.h"

class DatabaseDrawDeskClient {
 private:
    std::shared_ptr<DatabaseClient> client;

 public:
    DatabaseDrawDeskClient(std::shared_ptr<DatabaseClient> cl);
    json createDesk(json) const;
    json getDeskData(int deskId) const;
    json updateDeskData(json) const;
    json getBlocksFromDesk(int deskId) const;
};
