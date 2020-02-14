#include "gtest/gtest.h"

#include "../lists/kmp.hpp"

TEST(KnuthMorrisPratt, PrefixMatch) {
  EXPECT_EQ({0}, kmp_search("haystack", "hay"));
}
