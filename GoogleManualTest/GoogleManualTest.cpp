#pragma warning (push,1)
#include "gtest/gtest.h"
#pragma warning (pop)

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}