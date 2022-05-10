#ifndef TESTSDRAWING_H
#define TESTSDRAWING_H

#include "DrawingLogic.h"
#include "mockClient.h"

TEST(DrawingLogic, sendNewBlock) {
    MockHttpClient network;

    HttpClientData::Block convBlock;
    EXPECT_CALL(network, addBlock(convBlock)).Times(1);

    ViewDataStructures::Block newBlock;
    DrawingLogic drawing(&network);
    drawing.sendNewBlock(newBlock);
}

TEST(DrawingLogic, sendDeletedBlock) {
    MockHttpClient network;

    HttpClientData::Block convBlock;
    EXPECT_CALL(network, deleteBlock(convBlock.id)).Times(1);
    EXPECT_CALL(network, changeBlock(convBlock)).Times(4);

    ViewDataStructures::MindMapData map;
    for (int i = 0; i < 5; ++i) {
        map.blocks.append(ViewDataStructures::Block());
    }
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
