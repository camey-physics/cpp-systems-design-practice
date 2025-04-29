#include <gtest/gtest.h>
#include "SharedPtr.h"

TEST(SharedPtrTest, BasicUseCount) {
    SharedPtr<int> sp(10), sp2;
    EXPECT_EQ(sp.useCount(), 1);
    sp2 = sp;
    EXPECT_EQ(sp.useCount(), 2);
    SharedPtr<int> sp3(20);
    sp3 = sp2;
    EXPECT_EQ(sp.useCount(), 3);
    SharedPtr<int> sp4 = sp;
    EXPECT_EQ(sp.useCount(), 4);
    sp = sp;
    EXPECT_EQ(sp.useCount(), 4);
}

TEST(SharedPtrTest, DestructorTest) {
    SharedPtr<int> sp(10);
    for (int i = 0; i < 5; i++) {
        SharedPtr<int> spTemp = sp;
    }
    EXPECT_EQ(sp.useCount(), 1);
    {
        SharedPtr<int> spTemp = sp;
        SharedPtr<int> spTemp2 = sp;
        EXPECT_EQ(sp.useCount(), 3);
    }
    EXPECT_EQ(sp.useCount(), 1);
}

TEST(SharedPtrTest, DereferenceTest) {
    SharedPtr<int> sp(10);
    EXPECT_EQ(*sp, 10);
    *sp = 20;
    EXPECT_EQ(*sp, 20);
    SharedPtr<int> sp2 = sp;
    *sp2 = 30;
    EXPECT_EQ(*sp, 30);
    // SharedPtr<int> sp2;
}

TEST(SharedPtrTestFloat, DereferenceTest) {
    SharedPtr<float> sp(10);
    EXPECT_EQ(*sp, 10);
    *sp = 20;
    EXPECT_EQ(*sp, 20);
    SharedPtr<float> sp2 = sp;
    *sp2 = 30;
    EXPECT_EQ(*sp, 30);
    // SharedPtr<int> sp2;
}

TEST(SharedPtrTestArbitrary, DereferenceTest) {
    class square {
        public:
            square(float x = 5) {
                x_ = x;
            }
            square& operator=(const square& other) {
                x_ = other.x_;
                return *this;
            }
            float getLength_() const {
                return x_;
            }
            void setLength_(float x) {
                x_ = x;
            }
            float calcArea() {
                return x_ *x_;
            }
        private:
            float x_;
    };

    SharedPtr<square> sp(10);
    EXPECT_EQ((*sp).calcArea(), 100);
    (*sp).setLength_(20);
    EXPECT_EQ((*sp).calcArea(), 400);
    SharedPtr<square> sp2 = sp;
    *sp2 = 30;
    EXPECT_EQ((*sp2).calcArea(), 900);
}