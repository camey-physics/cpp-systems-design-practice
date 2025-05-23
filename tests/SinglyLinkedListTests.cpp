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
    EXPECT_THROW(l.front(), std::out_of_range);
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

TEST(SinglyLinkedListTest, MoveConstructor) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 20; ++i) {
        l.append(i);
    }
    float* fAddress[20];
    for (int i = 0; i < 20; ++i) {
        fAddress[i] = &l[i];
    }
    SinglyLinkedList<float> l2 = std::move(l);
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(fAddress[i], &l2[i]);
        EXPECT_EQ(l2[i], i);
    }
    EXPECT_EQ(l.size(), 0);
    EXPECT_EQ(l2.size(), 20);
}

TEST(SinglyLinkedListTest, MoveAssignment) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 20; ++i) {
        l.append(i);
    }
    float* fAddress[20];
    for (int i = 0; i < 20; ++i) {
        fAddress[i] = &l[i];
    }
    SinglyLinkedList<float> l2;
    l2 = std::move(l);
    for (int i = 0; i < 20; ++i) {
        EXPECT_EQ(fAddress[i], &l2[i]);
        EXPECT_EQ(l2[i], i);
    }
    EXPECT_EQ(l.size(), 0);
    EXPECT_EQ(l2.size(), 20);
}

TEST(SinglyLinkedListTest, EraseOutOfBounds) {
    SinglyLinkedList<float> l;
    EXPECT_THROW(l.erase(0), std::out_of_range);
    for (int i = 0; i < 10; ++i) {
        l.append(i);
    }
    EXPECT_THROW(l.erase(10), std::out_of_range);
}

TEST(SinglyLinkedListTest, EraseNonEmptyList) {
    {
        SinglyLinkedList<float> l;
        for (int i = 0; i < 10; ++i) {
            l.append(i);
        }
        l.erase(0);
        EXPECT_EQ(l.size(), 9);
        EXPECT_EQ(l.front(), 1);
    }
    {
        SinglyLinkedList<float> l;
        for (int i = 0; i < 10; ++i) {
            l.append(i);
        }
        l.erase(5);
        EXPECT_EQ(l.size(), 9);
        EXPECT_EQ(l[4], 4);
        EXPECT_EQ(l[5], 6);
    }
}

TEST(SinglyLinkedListTest, PopFrontEmptyList) {
    SinglyLinkedList<float> l;
    EXPECT_THROW(l.pop_front(), std::out_of_range);
    
}

TEST(SinglyLinkedListTest, PopFrontNonEmptyList) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 10; ++i) {
        l.append(i);
    }
    for (int i = 0; i < 10; ++i) {
        float data = l.pop_front();
        EXPECT_EQ(data, i);
    }   
}

TEST(SinglyLinkedListTest, PopBackEmptyList) {
    SinglyLinkedList<float> l;
    EXPECT_THROW(l.pop_back(), std::out_of_range);
    
}

TEST(SinglyLinkedListTest, PopBackNonEmptyList) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 10; ++i) {
        l.prepend(i);
    }
    for (int i = 0; i < 10; ++i) {
        float data = l.pop_back();
        EXPECT_EQ(data, i);
    }   
}

TEST(SinglyLinkedListTest, InsertEmptyList) {
    SinglyLinkedList<float> l;
    l.insert(0, 10);
    EXPECT_EQ(l[0], 10);
}


TEST(SinglyLinkedListTest, MultipleInsertMidList) {
    SinglyLinkedList<float> l;
    for (int i = 0; i < 10; ++i) {
        l.append(i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(l[i], i);
    }
    l.insert(5, 100);
    EXPECT_EQ(l[5], 100);
    EXPECT_EQ(l[6], 5);
    EXPECT_EQ(l.size(), 11);
    EXPECT_EQ(l.end(), 9);
}