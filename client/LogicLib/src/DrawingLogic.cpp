#include "DrawingLogic.h"

void DrawingLogic::sendNewBlock(const ViewDataStructures::Block &newBlock) {
    //check position

    HttpClientData::Block convBlock = convertBlock(newBlock);

    network->addBlock(convBlock);

    emit sendNewBlockIdToSession(convBlock.id);
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
    QFont newFont = newBlock.textFont;
    HttpClientData::Font font(newFont.family().toStdString(), newFont.pointSize(), newFont.weight(), newFont.italic());

    HttpClientData::Color fontColor;
    newBlock.textColor.getRgb(&fontColor.r, &fontColor.g, &fontColor.b);

    HttpClientData::Color borderColor;
    newBlock.borderColor.getRgb(&borderColor.r, &borderColor.g, &borderColor.b);

    HttpClientData::Color bgColor;
    newBlock.backgroundColor.getRgb(&bgColor.r, &bgColor.g, &bgColor.b);

    return HttpClientData::Block(newBlock.id, newBlock.parentId, newBlock.position.x(), newBlock.position.y(),
                     newBlock.text.toStdString(), font, fontColor, borderColor, bgColor);
}

ViewDataStructures::MindMapData DrawingLogic::convertMap(const HttpClientData::MindMapData &map) {
    ViewDataStructures::MindMapData convMap;
    for (auto it = map.blocks.cbegin(); it != map.blocks.cend(); ++it) {
        ViewDataStructures::Block block = reverseConvertBlock(*it);
        convMap.blocks.append(block);
    }

    return convMap;
}

ViewDataStructures::Block DrawingLogic::reverseConvertBlock(const HttpClientData::Block &block) {
    QFont font(QString::fromStdString(block.font.family), block.font.pointSize,
               block.font.weight, block.font.italic);

    QColor textColor = QColor(block.fontColor.r, block.fontColor.g, block.fontColor.b);

    QColor borderColor = QColor(block.fontColor.r, block.fontColor.g, block.fontColor.b);

    QColor backgroundColor = QColor(block.fontColor.r, block.fontColor.g, block.fontColor.b);

    return ViewDataStructures::Block(block.id, block.parentId, QPoint(block.posX, block.posY),
                 QString::fromStdString(block.text), font, textColor, borderColor, backgroundColor);
}

