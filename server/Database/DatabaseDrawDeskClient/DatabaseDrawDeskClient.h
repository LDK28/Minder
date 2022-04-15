#include "DatabaseClient.h"

class DatabaseDrawDeskClient {
   private:
    DatabaseClient *client;

   public:
    json getDeskData(int deskId);
    json updateDeskData(json);
};