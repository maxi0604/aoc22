#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

int main() {
  int64_t max = 0;
  int64_t cur = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (std::all_of(line.begin(), line.end(), isspace)) {
      if (cur > max)
        max = cur;

      cur = 0;
      continue;
    }

    cur += std::stoi(line);
  }

  std::cout << max;
}
