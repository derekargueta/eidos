#include "gtest/gtest.h"

#include "../lists/ull.hpp"
#include "../lists/ll.hpp"


TEST(UnrolledLinkedList, BasicCreation) {
  UnrolledLinkedList<int> ull{};
  EXPECT_EQ(ull.size(), 0);
  EXPECT_TRUE(ull.empty());
}

TEST(UnrolledLinkedList, AppendingWithLargeNodes) {
  UnrolledLinkedList<int> ull{};
  EXPECT_TRUE(ull.empty());

  ull.push_back(5);
  EXPECT_EQ(ull.size(), 1);
  EXPECT_EQ(ull.get(0), 5);
  EXPECT_EQ(ull.numberOfLinks(), 1);
  EXPECT_FALSE(ull.empty());

  ull.push_back(1);
  EXPECT_EQ(ull.size(), 2);
  EXPECT_EQ(ull.get(1), 1);
  EXPECT_EQ(ull.numberOfLinks(), 1);
  EXPECT_FALSE(ull.empty());

  ull.push_back(3);
  EXPECT_EQ(ull.size(), 3);
  EXPECT_EQ(ull.get(2), 3);
  EXPECT_EQ(ull.numberOfLinks(), 1);
  EXPECT_FALSE(ull.empty());

  ull.push_back(9);
  EXPECT_EQ(ull.size(), 4);
  EXPECT_EQ(ull.get(3), 9);
  EXPECT_EQ(ull.numberOfLinks(), 1);
  EXPECT_FALSE(ull.empty());
}

TEST(UnrolledLinkedList, AppendingWithSmallNodes) {
  UnrolledLinkedList<int> ull(2);
  EXPECT_TRUE(ull.empty());

  // [ , ] --> [5, ]
  ull.push_back(5);
  EXPECT_EQ(ull.size(), 1);
  EXPECT_EQ(ull.get(0), 5);
  EXPECT_EQ(ull.numberOfLinks(), 1);
  EXPECT_FALSE(ull.empty());

  // [5, ] --> [5, 1]
  ull.push_back(1);
  EXPECT_EQ(ull.size(), 2);
  EXPECT_EQ(ull.get(1), 1);
  EXPECT_EQ(ull.numberOfLinks(), 1);
  EXPECT_FALSE(ull.empty());

  // [5, 1] --> [5, ]~[1, 2]
  ull.push_back(3);
  EXPECT_EQ(ull.size(), 3);
  EXPECT_EQ(ull.get(2), 3);
  EXPECT_EQ(ull.numberOfLinks(), 2);
  EXPECT_FALSE(ull.empty());

  // [5, ]~[1, 2] --> [5, ]~[1, ]~[2, 3]
  ull.push_back(9);
  EXPECT_EQ(ull.size(), 4);
  EXPECT_EQ(ull.get(3), 9);
  EXPECT_EQ(ull.numberOfLinks(), 3);
  EXPECT_FALSE(ull.empty());
}

TEST(UnrolledLinkedList, GetFront) {
  UnrolledLinkedList<int> ull{};

  ull.push_back(1);
  ull.push_back(2);
  ull.push_back(3);

  EXPECT_EQ(ull.front(), 1);
}

TEST(UnrolledLinkedList, GetBack) {
  UnrolledLinkedList<int> ull{};

  ull.push_back(1);
  ull.push_back(2);
  ull.push_back(3);

  EXPECT_EQ(ull.back(), 3);
}

TEST(UnrolledLinkedList, StringRepresentation) {
  UnrolledLinkedList<int> ull{};

  ull.push_back(1);
  ull.push_back(2);
  ull.push_back(3);

  EXPECT_EQ(ull.str(), "{[1, 2, 3]}");
}

/////////////////////// List tests

TEST(LinkedList, BasicCreation) {
  LinkedList<int> ll{};
  EXPECT_EQ(ll.size(), 0);
  EXPECT_TRUE(ll.empty());
}

TEST(LinkedList, GetFront) {
  LinkedList<int> ll{};

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);

  EXPECT_EQ(ll.front(), 1);
}

TEST(LinkedList, PopFront) {
  LinkedList<int> ll{};

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);

  ll.pop_front();

  EXPECT_EQ(ll.front(), 2);
  EXPECT_EQ(ll.back(), 3);
}

TEST(LinkedList, PushFront) {
  LinkedList<int> ll{};

  ll.push_back(1);
  ll.push_back(2);
  ll.push_front(3);

  EXPECT_EQ(ll.front(), 3);
  EXPECT_EQ(ll.back(), 2);
}

TEST(LinkedList, PopBack) {
  LinkedList<int> ll{};

  ll.push_back(1);

  EXPECT_EQ(ll.size(), 1);
  EXPECT_EQ(ll.front(), 1);
  EXPECT_EQ(ll.back(), 1);
  EXPECT_EQ(ll.countNodes(), 1);

  ll.pop_back();

  EXPECT_EQ(ll.size(), 0);
  EXPECT_EQ(ll.countNodes(), 0);

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);

  EXPECT_EQ(ll.size(), 3);
  EXPECT_EQ(ll.front(), 1);
  EXPECT_EQ(ll.back(), 3);
  EXPECT_EQ(ll.countNodes(), 3);

  ll.pop_back();

  EXPECT_EQ(ll.size(), 2);
  EXPECT_EQ(ll.countNodes(), 2);
  EXPECT_EQ(ll.front(), 1);
  EXPECT_EQ(ll.back(), 2);

  ll.pop_back();

  EXPECT_EQ(ll.size(), 1);
  EXPECT_EQ(ll.countNodes(), 1);
  EXPECT_EQ(ll.front(), 1);
  EXPECT_EQ(ll.back(), 1);
}

TEST(LinkedList, ToArray) {
  LinkedList<int> ll{};

  ll.push_back(1);
  ll.push_back(2);
  ll.push_back(3);
  ll.push_back(4);
  ll.push_back(5);

  int* arr = ll.toArray();

  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(arr[i], i + 1);
  }

  delete[] arr;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

