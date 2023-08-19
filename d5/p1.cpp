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
  std::regex number_regex(" (\\d+   )+(?P<num>\\d+)");
  std::vector<std::string> stack_strings{};
  std::string line;
  int64_t n = 0;
  while (std::getline(std::cin, line)) {
    std::smatch smatch;
    if (std::regex_search(line, smatch, number_regex)) {
      break;
    }

    n = std::stoi(smatch[smatch.size() - 1]);
    stack_strings.push_back(line);
  }

  std::vector<std::stack<char>> stack(n, std::stack<char>());
  for (auto i = stack_strings.rbegin(); i != stack_strings.rend(); i++) {
  }
}
