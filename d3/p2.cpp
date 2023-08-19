#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <iterator>
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
  std::string rucksack1, rucksack2, rucksack3;
  int64_t acc = 0;
  while (std::cin >> rucksack1 >> rucksack2 >> rucksack3) {
    std::set rs1(rucksack1.begin(), rucksack1.end());
    std::set rs2(rucksack2.begin(), rucksack2.end());
    std::set rs3(rucksack3.begin(), rucksack3.end());
    std::string a_b_sect{};
    std::set_intersection(rs1.begin(), rs1.end(), rs2.begin(), rs2.end(),
                          std::inserter(a_b_sect, a_b_sect.begin()));

    std::string abc_sect{};

    std::set_intersection(a_b_sect.begin(), a_b_sect.end(), rs3.begin(),
                          rs3.end(), std::inserter(abc_sect, abc_sect.begin()));

    std::cout << abc_sect << std::endl;
    acc += item_value(abc_sect[0]);
  }

  std::cout << acc << std::endl;
}
