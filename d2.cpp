#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <string>
#include <vector>

int main() {
  std::multiset<int64_t, std::greater<>> top{};
  int64_t cur = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (std::all_of(line.begin(), line.end(), isspace)) {
      top.insert(cur);
      cur = 0;
      continue;
    }

    cur += std::stoi(line);
  }

  std::cout << std::accumulate(top.begin(), std::next(top.begin(), 4), 0)
            << std::endl;
}
