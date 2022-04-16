#include <vector>

#include "DatabaseClient.h"

class DatabaseSessionClient {
   private:
    DatabaseClient *client;

   public:
    json createSession();
    json addUsersInSession(json);
    bool checkSession(int id);
    json updateSession(json);
    json getSessionInfo(int id);
    json selectSessionsWithUser(int userId);
    json deleteSession(int id);
};