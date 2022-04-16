#ifndef CLIENTDATA_H
#define CLIENTDATA_H

#include <string>
#include <vector>

typedef enum {
    OK, ERROR
} returnCode;

struct Session {
    std::string id;
    std::string name;
    std::string password;
};

struct Settings {
    std::string ip;
    std::string port;
};

struct UsersList {
    std::vector<std::string> users;
};

#endif // CLIENTDATA_H
