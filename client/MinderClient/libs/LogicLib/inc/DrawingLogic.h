#ifndef DRAWING_H
#define DRAWING_H

#include <QtWidgets>

#include "HttpDataStructures.h"
#include "ViewDataStructures.h"
#include "HttpClient.hpp"

class DrawingLogic : public QObject {
Q_OBJECT
public:
    explicit DrawingLogic() = default;
    explicit DrawingLogic(HttpClient *network_, QTimer *timer_) : network(network_), timer(timer_) {}
    ~DrawingLogic() = default;
public slots:
    void sendNewBlock(const size_t sessionId, const ViewDataStructures::Block &newBlock);
    void getMindMapInSession(const size_t sessionId);
    void sendDeletedBlock(const ViewDataStructures::MindMapData &changedBlocks);
signals:
    void sendNewBlockIdToSession(const long newBlockId);
    void updateMindMapDataInSession(const ViewDataStructures::MindMapData &data);
    void block();
    void unblock();
private:
    HttpClient *network = nullptr;
    QTimer *timer = nullptr;

    HttpClientData::Block convertBlock(const ViewDataStructures::Block &newBlock);
    ViewDataStructures::MindMapData convertMap(const HttpClientData::MindMapData &map);
    ViewDataStructures::Block reverseConvertBlock(const HttpClientData::Block &block);
};

#endif // DRAWING_H
