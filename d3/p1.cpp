#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int item_value(char item) {
  if ('a' <= item && item <= 'z') {
    return item - 'a' + 1;
  } else {
    return item - 'A' + 27;
  }
}

int main() {
  std::string rucksack;
  int64_t acc = 0;
  while (std::cin >> rucksack) {
    std::set<char> first(rucksack.begin(),
                         std::next(rucksack.begin(), rucksack.length() / 2));

    int64_t score = 0;
    for (auto i = rucksack.begin() + rucksack.length() / 2; i < rucksack.end();
         i++) {
      if (first.count(*i)) {
        std::cout << *i << ": " << item_value(*i) << std::endl;
        score += item_value(*i);
        break;
      }
    }

    acc += score;
  }

  std::cout << acc << std::endl;
}
