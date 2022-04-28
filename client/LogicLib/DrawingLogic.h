#ifndef DRAWING_H
#define DRAWING_H

#include <QtWidgets>

#include "DataStructures.h"
#include "HttpClient.h"

class DrawingLogic : public QObject {
Q_OBJECT
public:
    explicit DrawingLogic() = default;
    explicit DrawingLogic(std::shared_ptr<HttpClient> network_) : network(network_) {}
    ~DrawingLogic() = default;
public slots:
    void sendNewBlock(const Block &newBlock);
    void getMindMapInSession(const size_t sessionId);
//    void deleteBlock();
//    void changeBlock();
//    void changeSize();
signals:
    void sendNewBlockIdToSession(const long newBlockId);
    void updateMindMapDataInSession(const MindMapData &data);
private:
    std::shared_ptr <HttpClient> network = nullptr;

    BlockData convertBlock(const Block &newBlock);
    MindMapData convertMap(const ListBlocks &map);
    Block reverseConvertBlock(const BlockData &block);
};

#endif // DRAWING_H
