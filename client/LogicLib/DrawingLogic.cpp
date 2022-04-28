#include "DrawingLogic.h"

void DrawingLogic::sendNewBlock(const Block &newBlock) {
    //check position??

    BlockData convBlock = convertBlock(newBlock);

    network->addBlock(convBlock);

    emit sendNewBlockIdToSession(convBlock.id);
}

void DrawingLogic::getMindMapInSession(const size_t sessionId) {
    ListBlocks getMap = network->getCurrentStateDesk(sessionId);

    MindMapData map = convertMap(getMap);

    emit updateMindMapDataInSession(map);
}

BlockData DrawingLogic::convertBlock(const Block &newBlock) {
    QFont newFont = newBlock.textFont;
    Font font(newFont.family().toStdString(), newFont.pointSize(), newFont.weight(), newFont.italic());

    Color fontColor;
    newBlock.textColor.getRgb(&fontColor.r, &fontColor.g, &fontColor.b);

    Color borderColor;
    newBlock.borderColor.getRgb(&borderColor.r, &borderColor.g, &borderColor.b);

    Color bgColor;
    newBlock.backgroundColor.getRgb(&bgColor.r, &bgColor.g, &bgColor.b);

    return BlockData(newBlock.id, newBlock.parentId, newBlock.position.x(), newBlock.position.y(),
                     newBlock.text.toStdString(), font, fontColor, borderColor, bgColor);
}

MindMapData DrawingLogic::convertMap(const ListBlocks &map) {
    MindMapData convMap;
    for (auto it = map.blocks.cbegin(); it != map.blocks.cend(); ++it) {
        Block block = reverseConvertBlock(*it);
        convMap.blocks.append(block);
    }

    return convMap;
}

Block DrawingLogic::reverseConvertBlock(const BlockData &block) {
    QFont font(QString::fromStdString(block.font.family), block.font.pointSize,
               block.font.weight, block.font.italic);

    QColor textColor = QColor(block.fontColor.r, block.fontColor.g, block.fontColor.b);

    QColor borderColor = QColor(block.fontColor.r, block.fontColor.g, block.fontColor.b);

    QColor backgroundColor = QColor(block.fontColor.r, block.fontColor.g, block.fontColor.b);

    return Block(block.id, block.parentId, QPoint(block.posX, block.posY),
                 QString::fromStdString(block.text), font, textColor, borderColor, backgroundColor);
}

