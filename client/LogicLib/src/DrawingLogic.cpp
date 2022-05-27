#include "DrawingLogic.h"

void DrawingLogic::sendNewBlock(const ViewDataStructures::Block &newBlock, const size_t sessionId) {
    HttpClientData::Block convBlock = convertBlock(newBlock);

    size_t id = network->addBlock(convBlock, sessionId);

    emit sendNewBlockIdToSession(id);
}

void DrawingLogic::sendDeletedBlock(const ViewDataStructures::MindMapData &changedBlocks) {
    for(int i = 1; i < changedBlocks.blocks.count(); ++i) {
        HttpClientData::Block convBlock = convertBlock(changedBlocks.blocks.at(i));
        network->changeBlock(convBlock);
    }
    network->deleteBlock(changedBlocks.blocks.at(0).id);
}

void DrawingLogic::getMindMapInSession(const size_t sessionId) {
    HttpClientData::MindMapData getMap = network->getCurrentStateDesk(sessionId);

    ViewDataStructures::MindMapData map = convertMap(getMap);

    emit updateMindMapDataInSession(map);
}

void DrawingLogic::sendReceivedNewBlock(const HttpClientData::Block &receivedBlock) {
    ViewDataStructures::Block convBlock = reverseConvertBlock(receivedBlock);

    emit addNewBlock(convBlock);
}

void DrawingLogic::sendReceivedDeletedBlock(size_t id) {
    emit deleteBlock(id);
}

HttpClientData::Block DrawingLogic::convertBlock(const ViewDataStructures::Block &newBlock) {
    HttpClientData::Font font(newBlock.textFont.toString().toStdString());

    HttpClientData::Color fontColor(newBlock.textColor.name().toStdString());

    HttpClientData::Color borderColor(newBlock.borderColor.name().toStdString());

    HttpClientData::Color bgColor(newBlock.backgroundColor.name().toStdString());

    return HttpClientData::Block(newBlock.id, newBlock.parentId, newBlock.position.x(), newBlock.position.y(),
                     newBlock.text.toStdString(), font, fontColor, borderColor, bgColor);
}

ViewDataStructures::MindMapData DrawingLogic::convertMap(const HttpClientData::MindMapData &map) {
    ViewDataStructures::MindMapData convMap;
    for (const auto &block: map.blocks) {
        ViewDataStructures::Block viewBlock = reverseConvertBlock(block);
        convMap.blocks.append(viewBlock);
    }

    return convMap;
}

ViewDataStructures::Block DrawingLogic::reverseConvertBlock(const HttpClientData::Block &block) {
    QFont font;
    font.fromString(QString::fromStdString(block.font.name));

    QColor textColor = QColor(QString::fromStdString(block.fontColor.name));

    QColor borderColor = QColor(QString::fromStdString(block.borderColor.name));

    QColor backgroundColor = QColor(QString::fromStdString(block.bgColor.name));

    return ViewDataStructures::Block(block.id, block.parentId, QPoint(block.posX, block.posY),
                 QString::fromStdString(block.text), font, textColor, borderColor, backgroundColor);
}

