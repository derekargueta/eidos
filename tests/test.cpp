#include "gtest/gtest.h"

#include "../lists/ull.hpp"


TEST(UnrolledLinkedList, BasicCreation) {
  UnrolledLinkedList<int> ull{};
  EXPECT_EQ(ull.size(), 0);
}

TEST(UnrolledLinkedList, AppendingWithLargeNodes) {
  UnrolledLinkedList<int> ull{};
  ull.push_back(5);
  EXPECT_EQ(ull.size(), 1);
  EXPECT_EQ(ull.get(0), 5);
  EXPECT_EQ(ull.numberOfLinks(), 1);

  ull.push_back(1);
  EXPECT_EQ(ull.size(), 2);
  EXPECT_EQ(ull.get(1), 1);
  EXPECT_EQ(ull.numberOfLinks(), 1);

  ull.push_back(3);
  EXPECT_EQ(ull.size(), 3);
  EXPECT_EQ(ull.get(2), 3);
  EXPECT_EQ(ull.numberOfLinks(), 1);

  ull.push_back(9);
  EXPECT_EQ(ull.size(), 4);
  EXPECT_EQ(ull.get(3), 9);
  EXPECT_EQ(ull.numberOfLinks(), 1);
}

TEST(UnrolledLinkedList, AppendingWithSmallNodes) {
  UnrolledLinkedList<int> ull(2);

  // [ , ] --> [5, ]
  ull.push_back(5);
  EXPECT_EQ(ull.size(), 1);
  EXPECT_EQ(ull.get(0), 5);
  EXPECT_EQ(ull.numberOfLinks(), 1);

  // [5, ] --> [5, 1]
  ull.push_back(1);
  EXPECT_EQ(ull.size(), 2);
  EXPECT_EQ(ull.get(1), 1);
  EXPECT_EQ(ull.numberOfLinks(), 1);

  // [5, 1] --> [5, ]~[1, 2]
  ull.push_back(3);
  EXPECT_EQ(ull.size(), 3);
  EXPECT_EQ(ull.get(2), 3);
  EXPECT_EQ(ull.numberOfLinks(), 2);

  // [5, ]~[1, 2] --> [5, ]~[1, ]~[2, 3]
  ull.push_back(9);
  EXPECT_EQ(ull.size(), 4);
  EXPECT_EQ(ull.get(3), 9);
  EXPECT_EQ(ull.numberOfLinks(), 3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

