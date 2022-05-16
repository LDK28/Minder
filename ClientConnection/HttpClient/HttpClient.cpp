#include "HttpClient.hpp"

// private
int InterfaceHttpClient::connectServer()
{
    this->sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->sd <= 0)
        throw std::runtime_error(std::string(strerror(errno)));

    // struct hostent* hp = gethostbyname("minder.com");

    struct sockaddr_in addr;   // Адрес сервера
    addr.sin_family = AF_INET; // Для интернет сокетов AF_INET !
    addr.sin_port = htons(80); // port
    addr.sin_addr.s_addr = inet_addr("8.8.8.8");
    // memcpy(&addr.sin_addr, hp->h_addr, hp->h_length);

    int connected = connect(this->sd, (struct sockaddr *)&addr, sizeof(addr));
    if (connected != 0)
        throw std::runtime_error(std::string(strerror(errno)));

    return 0;
}

int InterfaceHttpClient::sendMsg(std::string msg)
{
    size_t left = msg.size();
    ssize_t sent = 0;
    int flags = 0;
    while (left > 0)
    {
        sent = send(this->sd, msg.data() + sent, msg.size() - sent, flags);
        if (-1 == sent)
            throw std::runtime_error(std::string(strerror(errno)));
        left -= sent;
    }

    return 0;
}

std::string InterfaceHttpClient::recvMsg()
{
    int result;
    char buf[BUFFER_SIZE];
    int flags = 0;
    std::string msg;

    do
    {
        result = recv(this->sd, buf, BUFFER_SIZE, flags);
        if (result > 0)
            msg.append(std::string(buf));
        else
            throw std::runtime_error(std::string(strerror(errno)));

    } while (result > 0);

    return msg;
}

std::string InterfaceHttpClient::sendRequest(std::string &request)
{
    this->connectServer();

    this->sendMsg(request);

    std::string result = this->recvMsg();

    shutdown(this->sd, SHUT_RDWR);

    if (close(this->sd) == -1)
        throw std::runtime_error(std::string(strerror(errno)));

    return result;
}

// public
HttpClientData::returnCode updateSettings(const HttpClientData::SettingsData &){};

std::string checkConnectionToSession(const HttpClientData::SessionConnectionData &){};

size_t createSession(const HttpClientData::SessionCreationData &){};

void getUsers(const HttpClientData::SessionConnectionData &);

void addBlock(const HttpClientData::Block &, const HttpClientData::SessionConnectionData &){};

void changeBlock(const HttpClientData::Block &, const HttpClientData::SessionConnectionData &){};

void deleteBlock(const size_t id, const HttpClientData::SessionConnectionData &){};

HttpClientData::MindMapData InterfaceHttpClient::getCurrentStateDesk(const HttpClientData::SessionConnectionData &con)
{
    std::string id, password, request;
    id = std::to_string(con.id);
    password = con.password;
    request = "GET blocks " + id + " " + password;
    std::string serverMsg = sendRequest(request);
    json dataJson = json::parse(serverMsg);
    HttpClientData::MindMapData data;
    // data.blocks = dataJson["data"].get<std::vector<HttpClientData::Block>>();
    // data.blocks = dataJson["Configuration"];
    return data;
};

void disconnect(const size_t userId, const HttpClientData::SessionConnectionData &){};