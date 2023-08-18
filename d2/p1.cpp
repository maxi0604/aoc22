#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::map<char, int64_t> move_score = {{'X', 1}, {'Y', 2}, {'Z', 3}};

int64_t score(char their, char our) {
  switch (their) {
  case 'A':
    switch (our) {
    case 'X':
      return 3;
    case 'Y':
      return 6;
    case 'Z':
      return 0;
    }
  case 'B':
    switch (our) {
    case 'X':
      return 0;
    case 'Y':
      return 3;
    case 'Z':
      return 6;
    }
  case 'C':
    switch (our) {
    case 'X':
      return 6;
    case 'Y':
      return 0;
    case 'Z':
      return 3;
    }
  }

  return -(1 << 16);
}
int main() {
  int64_t acc_score = 0;
  char their, space, our, term;
  while (!std::cin.eof()) {
    std::cin >> their >> our;

    if (!std::cin.good()) {
      break;
    }
    std::cout << "score: " << move_score.find(our)->second << " + "
              << score(their, our) << std::endl;
    acc_score += move_score.find(our)->second;
    acc_score += score(their, our);
  }
  std::cout << acc_score << std::endl;
}
