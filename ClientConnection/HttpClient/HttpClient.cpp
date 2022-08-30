#include "HttpClient.hpp"

// private ------------------------------------------------
void HttpClient::connectServer()
{
    this->sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->sd <= 0)
        throw std::runtime_error(std::string(strerror(errno)));

    // struct hostent* hp = gethostbyname("minder.com");

    struct sockaddr_in addr;           // Адрес сервера
    addr.sin_family = AF_INET;         // Для интернет сокетов AF_INET !
    addr.sin_port = htons(this->port); // port
    addr.sin_addr.s_addr = inet_addr(this->ip.c_str());
    // memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);

    int connected = connect(this->sd, (struct sockaddr *)&addr, sizeof(addr));
    if (connected != 0)
        throw std::runtime_error(std::string(strerror(errno)));
}

void HttpClient::sendRequest(std::string &request)
{
    size_t left = request.size();
    ssize_t sent = 0;
    int flags = 0;
    while (left > 0)
    {
        sent = send(this->sd, request.data() + sent, request.size() - sent, flags);
        if (-1 == sent)
            throw std::runtime_error(std::string(strerror(errno)));
        left -= sent;
    }
}

std::string HttpClient::recvResponse()
{
    int result;
    char buf[BUFFER_SIZE] = "";
    int flags = 0;
    std::string response;

    do
    {
        result = recv(this->sd, buf, BUFFER_SIZE, flags);
        if (result > 0)
            response.append(std::string(buf));
        else
            throw std::runtime_error(std::string(strerror(errno)));

    } while (result == BUFFER_SIZE);

    return response;
}

std::string HttpClient::sendMsgWithResponse(std::string &request)
{
    this->connectServer();

    this->sendRequest(request);

    std::string result = this->recvResponse();

    shutdown(this->sd, SHUT_RDWR);

    if (close(this->sd) == -1)
        throw std::runtime_error(std::string(strerror(errno)));

    return result;
}

void HttpClient::sendMsgNoResponse(std::string &request)
{
    this->connectServer();

    this->sendRequest(request);

    shutdown(this->sd, SHUT_RDWR);

    if (close(this->sd) == -1)
        throw std::runtime_error(std::string(strerror(errno)));
}

// public -------------------------------------------------

// обновление настроек подключение к серверу(локально)
HttpClientData::returnCode HttpClient::updateSettings(const HttpClientData::SettingsData &settings)
{
    if (settings.ip.empty() || settings.port == 0)
        return HttpClientData::returnCode::FAILED;

    this->ip = settings.ip;
    this->port = settings.port;
    return HttpClientData::returnCode::SUCCESS;
};

// проверка сессии и верификация пароля, если есть: name сесcии, если нет
std::string HttpClient::checkConnectionToSession(const HttpClientData::SessionConnectionData &scData, const size_t &userId)
{
    json data;
    data["title"] = "CHECKCONNECTIONTOSESSION";
    data["session"] = JsonParser::SessionConnectionDataToJson(scData);
    data["userId"] = userId;

    std::string msg = data.dump();

    std::string response = this->sendMsgWithResponse(msg);
    return response;
};

// создание новой сессии: возвращаю id, иначе 0 (scData, userid)
size_t HttpClient::createSession(const HttpClientData::SessionCreationData &scData, const size_t &userId)
{
    json data;
    data["title"] = "CREATESESSION";
    data["session"] = JsonParser::SessionCreationDataToJson(scData);
    data["userId"] = userId;
    std::string request = data.dump();

    std::string response = this->sendMsgWithResponse(request);
    size_t id = std::stoi(response, nullptr, 10);

    return id;
};

// добавление блока в сессию //(... block, size_t deskId )
size_t HttpClient::addBlock(const HttpClientData::Block &block, const size_t &deskId)
{
    json data;
    data["deskId"] = deskId;
    data["block"] = JsonParser::BlockToJson(block);
    data["title"] = "ADDBLOCK";
    std::string request = data.dump();

    std::string response = this->sendMsgWithResponse(request);

    size_t blockId = std::stoi(response, nullptr, 10);
    return blockId;
}

// подменить блок
void HttpClient::changeBlock(const HttpClientData::Block &block)
{
    json data;
    data["block"] = JsonParser::BlockToJson(block);
    data["title"] = "CHANGEBLOCK";
    std::string request = data.dump();

    this->sendMsgNoResponse(request);
};

// удалить блок по id
void HttpClient::deleteBlock(const size_t &blockId)
{
    json data;
    data["title"] = "DELETEBLOCK";
    data["blockId"] = blockId;
    std::string request = data.dump();

    this->sendMsgNoResponse(request);
};

// получить все блоки по id сессии (size_t deskId)
HttpClientData::MindMapData HttpClient::getCurrentStateDesk(const size_t &sessionId)
{
    json data;
    data["title"] = "GETCURRENTSTATEDESK";
    data["sessionId"] = sessionId;
    std::string request = data.dump();

    std::string response = sendMsgWithResponse(request);
    json dataJson = json::parse(response);
    HttpClientData::MindMapData mmData;

    for (auto &elem : dataJson["blocks"])
        mmData.blocks.push_back(JsonParser::JsonToBlock(elem));
    return mmData;
};

HttpClientData::UsersInSessionData HttpClient::getUsersInSession(const size_t &sessionId)
{
    json data;
    data["title"] = "GETUSERS";
    data["sessionId"] = sessionId;
    std::string request = data.dump();

    std::string response = this->sendMsgWithResponse(request);
    json dataJson = json::parse(response);

    HttpClientData::UsersInSessionData users;

    for (auto &elem : dataJson["users"])
    {
        HttpClientData::User user;
        user.nickname = elem["username"];
        users.users.push_back(user);
    }
    return users;
}

size_t HttpClient::loginUser(const HttpClientData::UserData &userData)
{
    json data;
    data["title"] = "LOGINUSER";
    data["user"] = JsonParser::UserDataToJson(userData);
    std::string request = data.dump();

    std::string response = this->sendMsgWithResponse(request);

    size_t userId = std::stoi(response, nullptr, 10);
    return userId;
}

size_t HttpClient::registerUser(const HttpClientData::UserData &userData)
{
    json data;
    data["title"] = "REGISTERUSER";
    data["user"] = JsonParser::UserDataToJson(userData);
    std::string request = data.dump();

    std::string response = this->sendMsgWithResponse(request);

    size_t userId = std::stoi(response, nullptr, 10);
    return userId;
}

// удалить активного пользователя из сессии, но пользователь должен остаться
void HttpClient::disconnectSession(const size_t &userId, const size_t &sessionId)
{
    json data;
    data["title"] = "DISCONNECTSESSION";
    data["sessionId"] = sessionId;
    data["userId"] = userId;
    std::string request = data.dump();

    this->sendMsgNoResponse(request);
};

// true если есть изменения
// false если нет 
bool HttpClient::ping(const size_t &userId, const size_t &sessionId)
{
    json data;
    data["title"] = "PING";
    data["sessionId"] = sessionId;
    data["userId"] = userId;
    std::string request = data.dump();

    std::string response = this->sendMsgWithResponse(request);
    if (response == "1")
        return true;
    else
        return false;
};