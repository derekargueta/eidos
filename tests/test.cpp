#include "gtest/gtest.h"

#include "../lists/ull.hpp"


TEST(UnrolledLinkedList, BasicCreation) {
  UnrolledLinkedList<int> ull{};
  //EXPECT_TRUE(true);
  EXPECT_TRUE(ull.size() == 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

