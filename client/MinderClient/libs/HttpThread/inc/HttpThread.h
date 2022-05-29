#include <QThread>

#include "HttpClient.hpp"

class HttpThread : public QThread
 {
     Q_OBJECT

    HttpThread(HttpClient *httpClient_) : httpClient(httpClient_) {}

 protected:
     void run();
 private:
    HttpClient *httpClient;
 };
