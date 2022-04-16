#ifndef TESTSDRAWING_H
#define TESTSDRAWING_H

#include "Drawing.h"
#include "mockClient.h"

 TEST(Drawing, addBlock) {
     MockHttpClient network;
     EXPECT_CALL(network, changeDesk()).Times(1);

     Drawing drawing(&network);
     drawing.addBlock();
 }

 TEST(Drawing, deleteBlock) {
    MockHttpClient network;
    EXPECT_CALL(network, changeDesk()).Times(1);

    Drawing drawing(&network);
    drawing.deleteBlock();
 }

 TEST(Drawing, changeBlock) {
    MockHttpClient network;
    EXPECT_CALL(network, changeDesk()).Times(1);

    Drawing drawing(&network);
    drawing.changeBlock();
 }

TEST(Drawing, changeSize) {
    MockHttpClient network;
    EXPECT_CALL(network, changeDesk()).Times(1);

    Drawing drawing(&network);
    drawing.changeSize();
}

#endif // TESTSDRAWING_H
