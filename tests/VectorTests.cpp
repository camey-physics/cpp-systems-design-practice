#include <gtest/gtest.h>
#include "Vector.h"
#include <stdexcept>

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

TEST(VectorTest, UsingAt) {
    Vector<double> v2(10, 3.141592653589793);
    for (int i = 0; i < 10; ++i) {
        EXPECT_NEAR(v2.at(i), 3.141592653589793, 1e-14);
    }
}

TEST(VectorTest, OutOfBoundsErrorWithAt) {
    Vector<float> v2(10, 3.141592653589793);
    EXPECT_THROW(v2.at(11), std::out_of_range);
}

TEST(VectorTest, Size) {
    Vector<unsigned short> v(10,0);
    EXPECT_EQ(v.size(), 10);
}

TEST(VectorTest, Reserve) {
    Vector<char> v;
    v.reserve(10);
    EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorTest, ResizeLarger) {
    Vector<int> v(10,0);
    v.resize(20);
    EXPECT_EQ(v.size(), 20);
}

TEST(VectorTest, ResizeSmaller) {
    Vector<int> v(10,0);
    v.resize(5);
    EXPECT_EQ(v.size(), 5);
    EXPECT_EQ(v.capacity(), 10);
}
TEST(VectorTest, ResizeReuseIfCapacityLargeEnough) {
    Vector<int> v(10,0);
    int* oldPtr = &v[0];
    v.resize(5);
    EXPECT_EQ(v.capacity(), 10);
    EXPECT_EQ(&v[0], oldPtr);
}

TEST(VectorTest, ResizeInitializesOnlyNewElements) {
    Vector<int> v(5, 1);
    v.resize(10);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(v[i], 1);
    }
    for (int i = 5; i < 10; ++i) {
        EXPECT_EQ(v[i], 0);
    }
}

TEST(VectorTest, AssignmentOperatorReuseIfCapacityLargeEnough) {
    Vector<float> v(10,1.0), v2(5,3.1415);
    float* oldPtr = &v[0];
    v = v2;
    EXPECT_EQ(v.capacity(), 10);
    EXPECT_EQ(&v[0], oldPtr);
}

TEST(VectorTest, SelfAssignment) {
    Vector<long> v(10,3);
    v = v;
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(v[i], 3);
    }
}
TEST(VectorTest, PopBack) {
    Vector<float> v(10);
    v.pop_back();
    EXPECT_EQ(v.size(), 9);
    EXPECT_EQ(v.capacity(), 10);
}

TEST(VectorTest, PushBack) {
    Vector<float> v(10, 0);
    v.push_back(3.1415);
    EXPECT_EQ(v.size(), 11);
    EXPECT_NEAR(v[10], 3.1415, 1e-7);
    EXPECT_EQ(v.capacity(), 22);
}

TEST(VectorTest, DataPointerMatchesIndexZero) {
    Vector<int> v(10, 6);
    EXPECT_EQ(v.data(), &v[0]);
}