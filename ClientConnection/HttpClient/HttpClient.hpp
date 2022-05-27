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
#include "ClientData.h"

#define BUFFER_SIZE 512

class InterfaceHttpClient
{
private:
    virtual void sendRequest(std::string &request) = 0;
    virtual void connectServer() = 0;
    virtual std::string recvResponse() = 0;

public:
    InterfaceHttpClient(/* args */){};
    ~InterfaceHttpClient(){};

    // обновление настроек подключение к серверу(локально)
    virtual HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &) = 0;

    // проверка сессии и верификация пароля, если есть: name сесcии  и добавление юзера, если нет пустую строку (scData, userId)
    virtual std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &, const size_t &) = 0;

    // создание новой сессии: возвращаю id, иначе 0(Data, UserId)
    virtual size_t createSession(const HttpClientData::SessionCreationData &, const size_t &) = 0;

    // добавление блока в сессию //(... block, size_t deskId )
    virtual size_t addBlock(const HttpClientData::Block &, const size_t &) = 0;

    // подменить блок
    virtual void changeBlock(const HttpClientData::Block &) = 0;

    // удалить блок по id
    virtual void deleteBlock(const size_t &) = 0;

    // получить все блоки по id сессии(sessionID)
    virtual HttpClientData::MindMapData getCurrentStateDesk(const size_t &) = 0;

    // удалить активного пользователя из сессии(UserId, SessionId)
    virtual void disconnectSession(const size_t &, const size_t &) = 0;

    // Получение пользователей в сессии
    virtual HttpClientData::UsersInSessionData getUsersInSession(const size_t &) = 0;
    virtual size_t loginUser(const HttpClientData::UserData &) = 0;
    virtual size_t registerUser(const HttpClientData::UserData &) = 0;

    // virtual void updateDesk() = 0;
    // virtual void updateUsers() = 0;
};

class HttpClient : InterfaceHttpClient
{
private:
    std::string ip;
    int port;
    int sd; // socket descriptor

    void sendRequest(std::string &request) override;
    void connectServer() override;
    std::string recvResponse() override;

    std::string sendMsgWithResponse(std::string &request);
    void sendMsgNoResponse(std::string &request);

public:
    HttpClient(std::string _ip, int _port) : ip(_ip), port(_port){};
    ~HttpClient(){};

    // обновление настроек подключение к серверу(локально)
    HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &) override;

    // проверка сессии и верификация пароля, если есть: name сесcии  и добавление юзера, если нет пустую строку (scData, userId)
    std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &, const size_t &) override;

    // создание новой сессии: возвращаю id, иначе 0
    size_t createSession(const HttpClientData::SessionCreationData &, const size_t &) override;

    // get user names from session
    HttpClientData::UsersInSessionData getUsersInSession(const size_t &) override;

    // добавление блока в сессию: blockId
    size_t addBlock(const HttpClientData::Block &, const size_t &) override;

    // подменить блок
    void changeBlock(const HttpClientData::Block &) override;

    // удалить блок по id
    void deleteBlock(const size_t &) override;

    // получить все блоки по id сессии
    HttpClientData::MindMapData getCurrentStateDesk(const size_t &) override;

    // удалить активного пользователя из сессии
    void disconnectSession(const size_t &, const size_t &) override;

    size_t loginUser(const HttpClientData::UserData &) override;
    size_t registerUser(const HttpClientData::UserData &) override;

    // void updateDesk() override;
    // void updateUsers() override;
};
#endif