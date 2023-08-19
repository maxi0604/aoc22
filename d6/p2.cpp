#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <vector>

int main() {
  std::string str;
  std::cin >> str;
  size_t block_begin = 0;
  for (size_t i = 0; i < str.length(); ++i) {
    for (size_t j = block_begin; j < i; ++j) {
      if (str[i] == str[j]) {
        block_begin = j + 1;
      }

      if (i - block_begin >= 14) {
        std::cout << i;
        return 0;
      }
    }
  }
}
