#ifndef TESTSDRAWING_H
#define TESTSDRAWING_H

#include "DrawingLogic.h"
#include "mockClient.h"

TEST(DrawingLogic, sendNewBlock) {
    MockHttpClient network;

    size_t sessionId = 1;

    ViewDataStructures::Block newBlock;
    HttpClientData::Block convBlock(newBlock.id, newBlock.parentId, newBlock.position.x(),
        newBlock.position.y(), newBlock.text.toStdString(),
        HttpClientData::Font(newBlock.textFont.toString().toStdString()),
        HttpClientData::Color(newBlock.textColor.name().toStdString()),
        HttpClientData::Color(newBlock.borderColor.name().toStdString()),
        HttpClientData::Color(newBlock.backgroundColor.name().toStdString()));
    EXPECT_CALL(network, addBlock(convBlock, sessionId)).Times(1);

    DrawingLogic drawing(&network);
    drawing.sendNewBlock(newBlock, sessionId);
}

TEST(DrawingLogic, sendDeletedBlock) {
    MockHttpClient network;

    ViewDataStructures::MindMapData map;
    for (int i = 0; i < 5; ++i) {
        map.blocks.append(ViewDataStructures::Block());
    }

    ViewDataStructures::Block newBlock = map.blocks[0];

    HttpClientData::Block convBlock(newBlock.id, newBlock.parentId, newBlock.position.x(),
        newBlock.position.y(), newBlock.text.toStdString(),
        HttpClientData::Font(newBlock.textFont.toString().toStdString()),
        HttpClientData::Color(newBlock.textColor.name().toStdString()),
        HttpClientData::Color(newBlock.borderColor.name().toStdString()),
        HttpClientData::Color(newBlock.backgroundColor.name().toStdString()));
    EXPECT_CALL(network, deleteBlock(convBlock.id)).Times(1);
    EXPECT_CALL(network, changeBlock(convBlock)).Times(4);

    DrawingLogic drawing(&network);
    drawing.sendDeletedBlock(map);
}

TEST(DrawingLogic, getMindMapInSession) {
    MockHttpClient network;

    size_t sessionId = 1;
    EXPECT_CALL(network, getCurrentStateDesk(sessionId)).Times(1);

    DrawingLogic drawing(&network);
    drawing.getMindMapInSession(sessionId);
}

#endif // TESTSDRAWING_H
