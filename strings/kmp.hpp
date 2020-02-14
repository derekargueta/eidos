#pragma once

#include <string>
#include <vector>

/**
 * Implementation of the Knuth-Morris-Pratt string matching algorithm, based on
 * https://en.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm
 *
 * A naive algorithm would iterate down the search string (haystack) and attempt to
 * match a substring (needle) on each index of haystack. This has O(nk) complexity,
 * because it is logically equivalent to a nested for-loop where you try to match as much of
 * needle as possible, and move to the next index if it doesn't work.
 *
 * KMP achieves O(n+k) complexity by first doing a linear pass over the needle to compute a table
 * that is then leveraged in a linear pass of the haystack. The table helps
 *
 * TODO(dereka) switch away from std::vector to experiment with better performance.
 * TODO(dereka) use TMP for bring-your-own string implementation. The algorithm could then be
 *    generalized to any data structure with list-like properties (.size(), []-access, element
 *    comparison, etc.). Esp. with template deduction.
 */

/**
 * Pre-computes a search table from the needle (item being searched for). The table consists
 * of integers indicating what index to set the needle to by finding substrings that match the
 * "proper prefix" of the needle. If the search fails on a character which follows a substring that
 * matches the proper prefix
 * Example table for the string W "ABCDABD ":
 *     i	 0 1 2 3  4 5 6 7
 *   W[i]  A B C D  A B D
 *   T[i] -1 0 0 0 -1 0 2 0
 * T[6] = 2 because the two preceding characters "AB" match the proper prefix of W[:2]. Thus, if the
 * search fails on W[6], rather than going back to the beginning (W[0]) we start at W[2] since we already
 * know the preceding characters match, and take it from there.
 *
 * A `0` is used to indicate to restart the search from the beginning of the needle. Note, the beginning
 * character of the needle always maps to -1.
 *
 * A -1 is used to indicate that the search space (haystack) should be incremented by 1 character because
 * a match is deemed impossible.
 *
 * Combining the above 2 points, you may have a workflow where W[2] (C) is attempting to be matched on the
 * haystack, but it doesn't. So the table tells you to go to index 0 in the needle. The algorithm sees that
 * _that_ doesn't match either, so we need to shift the haystack down to get new data because the current
 * parameters are impossible to match.
 *
 * @return the table.
 */
std::vector<int> kmp_table(const std::string& needle) {
  std::vector<int> table(needle.size(), 0);
  int pos = 1;  // The current position we are computing in the table.
  int cnd = 0;  // The zero-based index in needle of the next character of the current candidate substring.

  table[0] = -1;  // This is always -1 because we can't backtrack from the beginning of the needle.

  // Linear run over the needle.
  while (pos < needle.size()) {
    if (needle[pos] == needle[cnd]) {
      table[pos] = table[cnd];
    } else {
      table[pos] = cnd;
      cnd = table[cnd]; // To increase performance.
      while (cnd >= 0 && needle[pos] != needle[cnd]) {
        cnd = table[cnd];
      }
    }
    pos += 1;
    cnd += 1;
  }

  table[pos] = cnd; // Only need when all word occurrences searched.
  return table;
}

/**
 * The search algorithm. Total runtime complexity is O(k + n) where k is the size of the needle and
 * n is the size of the haystack.
 * @param haystack the string to be searched.
 * @param needle the substring that we are searching for within haystack.
 * @return std::vector a vector of 0-based indices where needle was found in haystack. If no matches were found,
 *         returns an empty vector.
 */
std::vector<int> kmp_search(const std::string& haystack, const std::string& needle) {
  int haystack_position = 0;
  int needle_position = 0;

  // Construct a table to use for matching the needle against subindices of the haystack.
  // This operation is O(k) where k is the size of the needle.
  const auto table = kmp_table(needle);

  std::vector<int> results;

  // The search is linear, we do one sweep down the haystack to search for matches which makes this
  // portion of the algorithm O(n) where `n` is the size of the search space (haystack).
  while (haystack_position < haystack.size()) {
    if (needle[needle_position] == haystack[haystack_position]) {
      haystack_position += 1;
      needle_position += 1;
      if (needle_position == needle.size()) {
        /**
         * Occurrence found. If only the first occurrence is needed, m <- needle_position - haystack_position may be returned here.
         */
        results.push_back(haystack_position - needle_position);
        needle_position = table[needle_position]; // table[needle.size()] can't be -1
      }
    } else {
      // Get the new needle position from the table. If it's -1 then we need to increment each by
      // 1 which moves the haystack to the next character and brings us to the beginning of the needle.
      needle_position = table[needle_position];
      if (needle_position < 0) {
        haystack_position += 1;
        needle_position += 1;
      }
    }
  }

  return results;
}
