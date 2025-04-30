#include <gtest/gtest.h>
#include "Vector.h"

TEST(VectorTest, DefaultConstructor) {
    Vector<int> v;
}

TEST(VectorTest, ConstructorWithDefaultInitialization) {
    Vector<float> v2(10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(v2[i], 0.0);
    }
}

TEST(VectorTest, ConstructorWithNonZeroDefaultInitialization) {
    Vector<double> v2(10, 3.141592653589793);
    for (int i = 0; i < 10; ++i) {
        EXPECT_NEAR(v2[i], 3.141592653589793, 1e-14);
    }
}