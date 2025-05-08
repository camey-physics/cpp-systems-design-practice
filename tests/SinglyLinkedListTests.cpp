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

TEST(SinglyLinkedListTest, RemoveElement) {
    SinglyLinkedList<float> l;
    l.append(10.0);
    l.append(20.0);
    l.append(30.0);
    l.remove(20);
    EXPECT_NEAR(l.end(), 30.0, 1e-7);
}

TEST(SinglyLinkedListTest, RemoveLastElement) {
    SinglyLinkedList<float> l;
    l.append(10.0);
    l.append(20.0);
    l.append(30.0);
    l.remove(30);
    EXPECT_NEAR(l.end(), 20.0, 1e-7);
}

TEST(SinglyLinkedListTest, RemoveFirstElement) {
    SinglyLinkedList<float> l;
    l.append(10.0);
    l.append(20.0);
    l.append(30.0);
    l.remove(10);
    EXPECT_NEAR(l.front(), 20.0, 1e-7);
}

TEST(SinglyLinkedListTest, EmptyListSize) {
    SinglyLinkedList<float> l;
    EXPECT_EQ(l.size(), 0);
}

TEST(SinglyLinkedListTest, NonEmptyConstructorSize) {
    SinglyLinkedList<float> l(10);
    EXPECT_EQ(l.size(), 1);
}

TEST(SinglyLinkedListTest, AppendedListSize) {
    SinglyLinkedList<float> l(20);
    l.append(10);
    EXPECT_EQ(l.size(), 2);
}

TEST(SinglyLinkedListTest, PrependedListSize) {
    SinglyLinkedList<float> l;
    l.prepend(10);
    EXPECT_EQ(l.size(), 1);
}

TEST(SinglyLinkedListTest, RemovedElementListSize) {
    SinglyLinkedList<float> l(20);
    l.prepend(10);
    l.remove(10);
    EXPECT_EQ(l.size(), 1);
}

TEST(SinglyLinkedListTest, SeveralRemovedElementsListSize) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 20; i++) {
        l.prepend(i*2);
    }
    for (int i = 0; i < 10; i += 2) {
        l.remove(i);
    }
    EXPECT_EQ(l.size(), 15);
}

TEST(SinglyLinkedListTest, ClearNonEmptyList) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 20; i++) {
        l.prepend(i*2);
    }
    l.clear();
    EXPECT_EQ(l.size(), 0);
}

TEST(SinglyLinkedListTest, AccessOperatorOverload) {
    SinglyLinkedList<int> l;
    for (int i = 0; i < 10; i++) {
        l.append(i);
    }
    for (int i = 0; i < 10; i += 2) {
        EXPECT_EQ(l[i], i);
    }
}

TEST(SinglyLinkedListTest, EmptyListCopyConstructor) {
    SinglyLinkedList<float> l;
    SinglyLinkedList<float> l2(l);
    EXPECT_EQ(l2.size(), 0);
}

TEST(SinglyLinkedListTest, NonEmptyListCopyConstructor) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 10; ++i) {
        l.append(i);
    }
    SinglyLinkedList<float> l2 = l;
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(l2[i], l[i]);
    }
}

TEST(SinglyLinkedListTest, NonEmptyListCopyAssignment) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 10; ++i) {
        l.append(i);
    }
    SinglyLinkedList<float> l2;
    l2 = l;
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(l2[i], l[i]);
    }
}

TEST(SinglyLinkedListTest, CopyMutationProtection) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 10; ++i) {
        l.append(i);
    }
    SinglyLinkedList<float> l2;
    l2 = l;
    l.prepend(100);
    EXPECT_EQ(l2[0], 0);
}

TEST(SinglyLinkedListTest, SelfAssignment) {
    SinglyLinkedList<float> l(10);
    l = l;
    EXPECT_EQ(l[0], 10);
}