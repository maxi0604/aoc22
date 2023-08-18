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
char play_which(char their, char win_or_lose) {
  switch (their) {
  case 'A':
    switch (win_or_lose) {
    case 'X':
      return 'Z';
    case 'Y':
      return 'X';
    case 'Z':
      return 'Y';
    }
  case 'B':
    switch (win_or_lose) {
    case 'X':
      return 'X';
    case 'Y':
      return 'Y';
    case 'Z':
      return 'Z';
    }
  case 'C':
    switch (win_or_lose) {
    case 'X':
      return 'Y';
    case 'Y':
      return 'Z';
    case 'Z':
      return 'X';
    }
  }

  return -(1 << 7);
}
int main() {
  int64_t acc_score = 0;
  char their, win_or_lose;
  while (!std::cin.eof()) {
    std::cin >> their >> win_or_lose;
    char our = play_which(their, win_or_lose);
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
