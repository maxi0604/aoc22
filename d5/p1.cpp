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
  std::regex number_regex(" (\\d+   )+(\\d+)");
  std::vector<std::string> stack_strings{};
  std::string line;
  int64_t n_stacks = 0;
  while (std::getline(std::cin, line)) {
    std::smatch smatch;
    if (std::regex_search(line, smatch, number_regex)) {

      n_stacks = std::stoi(smatch[smatch.size() - 1]);
      break;
    }

    stack_strings.push_back(line);
  }

  std::vector<std::stack<char>> stacks(n_stacks, std::stack<char>());
  for (auto i = stack_strings.rbegin(); i != stack_strings.rend(); i++) {
    for (size_t j = 1; j < i->length(); j += 4) {
      char c = (*i)[j];
      if ('A' <= c && c <= 'Z') {
        stacks[j / 4].push(c);
      }
    }
  }

  std::regex move_regex("move (\\d+) from (\\d+) to (\\d+)");

  std::string move;
  while (std::getline(std::cin, move)) {
    std::smatch move_match;
    if (!std::regex_search(move, move_match, move_regex)) {
      continue;
    }
    int64_t n, a, b;
    n = std::stol(move_match[1]);
    a = std::stol(move_match[2]);
    b = std::stol(move_match[3]);
    std::cout << "parsed: " << n << " from " << a << "to" << b << std::endl;
    for (int64_t i = 0; i < n; i++) {
      stacks[b - 1].push(stacks[a - 1].top());
      stacks[a - 1].pop();
    }
  }

  for (auto &s : stacks) {
    std::cout << s.top();
  }

  std::cout << std::endl;
}
