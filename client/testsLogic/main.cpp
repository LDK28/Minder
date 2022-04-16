#include "mockClient.h"
#include "testsLogicController.h"
#include "testsUser.h"
#include "testsDrawing.h"

#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
