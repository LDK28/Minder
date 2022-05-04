#ifndef TESTSDRAWING_H
#define TESTSDRAWING_H

#include "DrawingLogic.h"
#include "mockClient.h"

TEST(DrawingLogic, sendNewBlock) {
    std::shared_ptr <MockHttpClient> network(new MockHttpClient);

    BlockData convBlock;
    EXPECT_CALL(*network, addBlock(convBlock)).Times(1);

    Block newBlock;
    DrawingLogic drawing(network);
    drawing.sendNewBlock(newBlock);
}

TEST(DrawingLogic, getMindMapInSession) {
    std::shared_ptr <MockHttpClient> network(new MockHttpClient);

    size_t sessionId = 1;
    EXPECT_CALL(*network, getCurrentStateDesk(sessionId)).Times(1);

    DrawingLogic drawing(network);
    drawing.getMindMapInSession(sessionId);
}

#endif // TESTSDRAWING_H
