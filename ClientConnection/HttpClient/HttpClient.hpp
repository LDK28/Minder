#ifndef HTTP_CLIENT_HPP
#define HTTP_CLIENT_HPP

#include <iostream>

#include <sys/socket.h> // connect, AF_INET
#include <netdb.h>      // gethostbyname
#include <netinet/in.h> // struct sockaddr_in
#include <arpa/inet.h>
#include <unistd.h>

#include "HttpClient.hpp"
#include "JsonParser.hpp"
#include "HttpClientData.hpp"

#define BUFFER_SIZE 512

class HttpClient
{
private:
    virtual std::string sendRequest(std::string &) = 0;

public:
    HttpClient(/* args */){};
    ~HttpClient(){};

    // обновление настроек подключение к серверу(локально)
    virtual HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &) = 0;

    // проверка сессии и верификация пароля, если есть: name сесcии, если нет
    virtual std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &) = 0;

    // создание новой сессии: возвращаю id, иначе 0
    virtual size_t createSession(const HttpClientData::SessionCreationData &) = 0;

    // get user names *from server
    virtual std::string getUsers(const HttpClientData::SessionConnectionData &) = 0;

    // добавление блока в сессию, узнать у Димы нужен ли пароль или только id
    virtual void addBlock(const HttpClientData::Block &, const HttpClientData::SessionConnectionData &) = 0;

    // подменить блок
    virtual void changeBlock(const HttpClientData::Block &, const HttpClientData::SessionConnectionData &) = 0;

    // удалить блок по id
    virtual void deleteBlock(const size_t id, const HttpClientData::SessionConnectionData &) = 0;

    // получить все блоки по id сессии
    virtual HttpClientData::MindMapData getCurrentStateDesk(const HttpClientData::SessionConnectionData &) = 0;

    // удалить активного пользователя из сессии
    virtual void disconnect(const size_t userId, const HttpClientData::SessionConnectionData &) = 0;

    virtual void updateDesk() = 0;
    virtual void updateUsers() = 0;
};

class InterfaceHttpClient : HttpClient
{
private:
    std::string ip;
    int port;
    int sd; // socket descriptor

    std::string sendRequest(std::string &request) override;
    int connectServer();
    int sendMsg(std::string msg);
    std::string recvMsg();

public:
    InterfaceHttpClient(/* args */){};
    ~InterfaceHttpClient(){};

    // обновление настроек подключение к серверу(локально)
    HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &) override;

    // проверка сессии и верификация пароля, если есть: name сесcии, если нет
    std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &) override;

    // создание новой сессии: возвращаю id, иначе 0
    size_t createSession(const HttpClientData::SessionCreationData &) override;

    // get user names *from server
    std::string getUsers(const HttpClientData::SessionConnectionData &) override;

    // добавление блока в сессию, узнать у Димы нужен ли пароль или только id
    void addBlock(const HttpClientData::Block &, const HttpClientData::SessionConnectionData &) override;

    // подменить блок
    void changeBlock(const HttpClientData::Block &, const HttpClientData::SessionConnectionData &) override;

    // удалить блок по id
    void deleteBlock(const size_t id, const HttpClientData::SessionConnectionData &) override;

    // получить все блоки по id сессии
    HttpClientData::MindMapData getCurrentStateDesk(const HttpClientData::SessionConnectionData &con) override;

    // удалить активного пользователя из сессии
    void disconnect(const size_t userId, const HttpClientData::SessionConnectionData &) override;

    void updateDesk() override;
    void updateUsers() override;
};
#endif