#include "HttpThread.h"

void HttpThread::run()
{
    int sessionId = 1;
    while(true) {
        QThread::sleep(2);
        HttpClientData::MindMapData mindMap = httpClient->getCurrentStateDesk(sessionId);
        //вызов отрисовки mindMap
    }
}
