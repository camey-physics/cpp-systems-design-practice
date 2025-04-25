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
    SharedPtr sp4 = sp;
    EXPECT_EQ(sp.useCount(), 4);
    sp = sp;
    EXPECT_EQ(sp.useCount(), 4);
}

TEST(SharedPtrTest, DestructorTest) {
    SharedPtr sp(10);
    for (int i = 0; i < 5; i++) {
        SharedPtr spTemp = sp;
    }
    EXPECT_EQ(sp.useCount(), 1);
    {
        SharedPtr spTemp = sp;
        SharedPtr spTemp2 = sp;
        EXPECT_EQ(sp.useCount(), 3);
    }
    EXPECT_EQ(sp.useCount(), 1);
}

TEST(SharedPtrTest, DereferenceTest) {
    SharedPtr sp(10);
    EXPECT_EQ(*sp, 10);
    *sp = 20;
    EXPECT_EQ(*sp, 20);
    SharedPtr sp2 = sp;
    *sp2 = 30;
    EXPECT_EQ(*sp, 30);
}