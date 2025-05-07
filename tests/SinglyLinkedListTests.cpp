#include <gtest/gtest.h>
#include "SinglyLinkedList.h"
#include <stdexcept>

TEST(SinglyLinkedListTest, DefaultConstructor) {
    SinglyLinkedList<int> l;
}

TEST(SinglyLinkedListTest, NonEmptyConstructor) {
    SinglyLinkedList<float> l(10.0);
}

TEST(SinglyLinkedListTest, NonEmptyListFront) {
    SinglyLinkedList<double> l(10.0);
    EXPECT_NEAR(l.front(), 10.0, 1e-14);
}

TEST(SinglyLinkedListTest, EmptyListFront) {
    SinglyLinkedList<int> l;
    EXPECT_THROW(l.front(), std::runtime_error);
}

TEST(SinglyLinkedListTest, EmptyListPrepend) {
    SinglyLinkedList<float> l;
    l.prepend(10.0);
    EXPECT_NEAR(l.front(), 10.0, 1e-7);
}

TEST(SinglyLinkedListTest, EmptyListPrependSeveralTimes) {
    SinglyLinkedList<float> l;
    l.prepend(10.0);
    l.prepend(20.0);
    l.prepend(30.0);
    EXPECT_NEAR(l.front(), 30.0, 1e-7);
}

TEST(SinglyLinkedListTest, NonEmptyListContains) {
    SinglyLinkedList<double> l(10.0);
    EXPECT_TRUE(l.contains(10.0));
}

TEST(SinglyLinkedListTest, EmptyListContains) {
    SinglyLinkedList<int> l;
    EXPECT_FALSE(l.contains(10.0));
}

TEST(SinglyLinkedListTest, EmptyListAppend) {
    SinglyLinkedList<float> l;
    l.append(10.0);
    EXPECT_NEAR(l.front(), 10.0, 1e-7);
    EXPECT_NEAR(l.end(), 10.0, 1e-7);
}

TEST(SinglyLinkedListTest, EmptyListAppendSeveralTimes) {
    SinglyLinkedList<float> l;
    l.append(10.0);
    l.append(20.0);
    l.append(30.0);
    EXPECT_NEAR(l.end(), 30.0, 1e-7);
}