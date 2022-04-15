#include <vector>

#include "DatabaseClient.h"

class DatabaseSessionClient {
   private:
    DatabaseClient *client;

   public:
    json createSession(json);
    json addUsersInSession(json);
    bool checkSession(int id);
    json getSessionInfo(int id);
    std::vector<int> selectSessionsWithUser(int userId);
    json deleteSession(int id);
};