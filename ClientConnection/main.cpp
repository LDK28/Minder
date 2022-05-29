#include "HttpClient.hpp"

int main(void){
    HttpClient httpClient("127.0.0.1", 1025);
    HttpClientData::SessionCreationData sc("motherfucker", "12345");
    size_t s = httpClient.createSession(sc, 2);
    std::cout << s;
    return 0;
}