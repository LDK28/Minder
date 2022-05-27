#ifndef DRAWING_H
#define DRAWING_H

#include <QtWidgets>

#include "DataStructures.h"
#include "HttpClient.h"

class DrawingLogic : public QObject {
Q_OBJECT
public:
    explicit DrawingLogic() = default;
    explicit DrawingLogic(HttpClient *network_) : network(network_) {}
    ~DrawingLogic() = default;
public slots:
    void sendNewBlock(const ViewDataStructures::Block &newBlock, const size_t);
    void getMindMapInSession(const size_t sessionId);
    void sendDeletedBlock(const ViewDataStructures::MindMapData &changedBlocks);

    void sendReceivedNewBlock(const HttpClientData::Block &receivedBlock);
    void sendReceivedDeletedBlock(size_t id);
signals:
    void sendNewBlockIdToSession(const long newBlockId);
    void updateMindMapDataInSession(const ViewDataStructures::MindMapData &data);
    void addNewBlock(const ViewDataStructures::Block &);
    void deleteBlock(size_t id);
private:
    HttpClient *network = nullptr;

    HttpClientData::Block convertBlock(const ViewDataStructures::Block &newBlock);
    ViewDataStructures::MindMapData convertMap(const HttpClientData::MindMapData &map);
    ViewDataStructures::Block reverseConvertBlock(const HttpClientData::Block &block);
};

#endif // DRAWING_H
