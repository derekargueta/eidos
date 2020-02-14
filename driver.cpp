#include "strings/kmp.hpp"

#include <iostream>
#include <string>

int main() {
  const std::string haystack = "haystack";
  const std::string needle = "sta";

  std::cout << "beginning search" << std::endl;
  const auto result = kmp_search(haystack, needle);
  std::cout << result.size() << std::endl;
  std::cout << result[0] << std::endl;
}
