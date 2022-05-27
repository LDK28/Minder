#include "HttpClient.hpp"

// private ------------------------------------------------
void InterfaceHttpClient::connectServer()
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

void InterfaceHttpClient::sendRequest(std::string &request)
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

std::string InterfaceHttpClient::recvResponse()
{
    int result;
    char buf[BUFFER_SIZE];
    int flags = 0;
    std::string response;

    do
    {
        result = recv(this->sd, buf, BUFFER_SIZE, flags);
        if (result > 0)
            response.append(std::string(buf));
        else
            throw std::runtime_error(std::string(strerror(errno)));

    } while (result > 0);

    return response;
}

std::string InterfaceHttpClient::sendMsgWithResponse(std::string &request)
{
    this->connectServer();

    this->sendRequest(request);

    std::string result = this->recvResponse();

    shutdown(this->sd, SHUT_RDWR);

    if (close(this->sd) == -1)
        throw std::runtime_error(std::string(strerror(errno)));

    return result;
}

void InterfaceHttpClient::sendMsgNoResponse(std::string &request)
{
    this->connectServer();

    this->sendRequest(request);

    shutdown(this->sd, SHUT_RDWR);

    if (close(this->sd) == -1)
        throw std::runtime_error(std::string(strerror(errno)));

}

// public -------------------------------------------------

// обновление настроек подключение к серверу(локально)
HttpClientData::returnCode InterfaceHttpClient::updateSettings(const HttpClientData::SettingsData &settings)
{
    if (settings.ip.empty() || settings.port == 0)
        return HttpClientData::returnCode::FAILED;

    this->ip = settings.ip;
    this->port = settings.port;
    return HttpClientData::returnCode::SUCCESS;
};

// проверка сессии и верификация пароля, если есть: name сесcии, если нет
std::string InterfaceHttpClient::checkConnectionToSession(const HttpClientData::SessionConnectionData &scData)
{
    json data = JsonParser::SessionConnectionDataToJson(scData);
    data["title"] = "CHECKCONNECTIONTOSESSION";
    std::string msg = data.dump();

    this->sendRequest(msg);
    std::string response = this->sendMsgWithResponse(msg);

    return response;
};

// создание новой сессии: возвращаю id, иначе 0
size_t InterfaceHttpClient::createSession(const HttpClientData::SessionCreationData &scData)
{
    json data = JsonParser::SessionCreationDataToJson(scData);
    data["title"] = "CREATESESSION";
    std::string request = data.dump();

    std::string response = this->sendMsgWithResponse(request);
    size_t id = std::stoi(response, nullptr, 10);

    return id;
};

// get user names *from server
std::string InterfaceHttpClient::getUsers(const HttpClientData::SessionConnectionData &scData)
{
    json data = JsonParser::SessionConnectionDataToJson(scData);
    data["title"] = "GETUSERS";
    std::string request = data.dump();

    std::string response = this->sendMsgWithResponse(request);

    return response;
}

// добавление блока в сессию
void InterfaceHttpClient::addBlock(const HttpClientData::Block &block, const HttpClientData::SessionConnectionData &scData)
{
    json data;
    data["connection"] = JsonParser::SessionConnectionDataToJson(scData);
    data["block"] = JsonParser::BlockToJson(block);
    data["title"] = "ADDBLOCK";
    std::string request = data.dump();

    this->sendMsgNoResponse(request);
}
// подменить блок
void InterfaceHttpClient::changeBlock(const HttpClientData::Block &block, const HttpClientData::SessionConnectionData &scData){
    json data;
    data["connection"] = JsonParser::SessionConnectionDataToJson(scData);
    data["block"] = JsonParser::BlockToJson(block);
    data["title"] = "CHANGEBLOCK";
    std::string request = data.dump();

    this->sendMsgNoResponse(request);
};

// удалить блок по id
void InterfaceHttpClient::deleteBlock(const size_t blockId, const HttpClientData::SessionConnectionData &scData)
{
    json data = JsonParser::SessionConnectionDataToJson(scData);
    data["title"] = "DELETEBLOCK";
    data["blockId"] = blockId;
    std::string request = data.dump();

    this->sendMsgNoResponse(request);
};

// получить все блоки по id сессии
HttpClientData::MindMapData InterfaceHttpClient::getCurrentStateDesk(const HttpClientData::SessionConnectionData &scData)
{
    json data = JsonParser::SessionConnectionDataToJson(scData);
    data["title"] = "GETCURRENTSTATEDESK";
    std::string request = data.dump();

    std::string response = sendMsgWithResponse(request);
    json dataJson = json::parse(response);
    HttpClientData::MindMapData mmData;
    // mmData.blocks = dataJson.get<std::vector<HttpClientData::Block>>();
    return mmData;
};

// удалить активного пользователя из сессии
void InterfaceHttpClient::disconnect(const size_t userId, const HttpClientData::SessionConnectionData &scData){
    json data = JsonParser::SessionConnectionDataToJson(scData);
    data["title"] = "ADDBLOCK";
    std::string request = data.dump();

    this->sendMsgNoResponse(request);
};