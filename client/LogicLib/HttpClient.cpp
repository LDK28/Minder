#include "HttpClient.h"

returnCode HttpClient::updateSettings(const Settings &) {
    return SUCCESS;
}

std::string HttpClient::checkConnectionToSession(const ExistSession &) {
    return "Session1";
}

size_t HttpClient::createSession(const NewSession &) {
    return 1;
}

void HttpClient::addBlock(const BlockData &) {
    return;
}

ListBlocks HttpClient::getCurrentStateDesk(const size_t) {
    return ListBlocks();
}

void HttpClient::disconnect() {
    return;
}

