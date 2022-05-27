#include <map>
#include <string>

#include "DatabaseClient.h"

class DatabaseUsersClient {
   private:
    DatabaseClient *client;

   public:
    json createUser(json);
    bool checkUser(json);
    json getAllUsersInfo();
    json getUserInfo(int id);
    json selectUsersByName(std::string name);
    json deleteUsersById(int id);

};