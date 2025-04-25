#include <gtest/gtest.h>
#include "SharedPtr.h"

TEST(SharedPtrTest, BasicUseCount) {
    SharedPtr sp(10), sp2;
    EXPECT_EQ(sp.useCount(), 1);
    sp2 = sp;
    EXPECT_EQ(sp.useCount(), 2);
    SharedPtr sp3(20);
    sp3 = sp2;
    EXPECT_EQ(sp.useCount(), 3);
    for (int i = 0; i < 5; i++) {
        SharedPtr spTemp = sp3;
    }
    EXPECT_EQ(sp.useCount(), 3);
}

// TEST(SharedPtrTest, BasicUseCount) {
//     SharedPtr sp(10), sp2;
//     sp2 = sp;
//     EXPECT_EQ(sp.useCount(), 2);
// }