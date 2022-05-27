#include "NetworkController.hpp"

std::string NetworkController::recvMsg(int sd)
{
    int result;
    char buf[BUFFER_SIZE];
    int flags = 0;
    std::string msg;

    do
    {
        result = recv(sd, buf, BUFFER_SIZE, flags);
        if (result > 0)
            msg.append(std::string(buf));
        else
            throw std::runtime_error(std::string(strerror(errno)));

    } while (result > 0);

    return msg;
}

void NetworkController::sendMsg(std::string msg, int sd)
{
    size_t left = msg.size();
    size_t sent = 0;
    int flags = 0;
    while (left > 0)
    {
        sent = send(sd, msg.data() + sent, msg.size() - sent, flags);
        if (sent == -1)
            throw std::runtime_error(std::string(strerror(errno)));
        left -= sent;
    }
}

void NetworkController::startServer()
{
    int opt = 1;
    this->sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (setsockopt(this->sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
        throw std::runtime_error(std::string(strerror(errno)));

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Will be changed on real address
    serv_addr.sin_port = htons(80);
    if (bind(this->sd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        throw std::runtime_error("bind: " + std::string(strerror(errno)));

    while (true)
    {
        listen(this->sd, 10);

        struct sockaddr_in client;
        socklen_t cli_len = sizeof(client);

        int clientSD = accept(this->sd, (struct sockaddr *)&client, &cli_len);

        std::cout << "+client: " << clientSD
                  << ", from: " << inet_ntoa(client.sin_addr)
                  << std::endl;

        std::string request = this->recvMsg(clientSD);
        std::string response = serverLogic.router(request);
        this->sendMsg(response, clientSD);
    }

    shutdown(this->sd, SHUT_RDWR);
    close(this->sd);
}
