#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

int64_t snafutoll(std::deque<int16_t> snafu) {
  int64_t result = 0;
  int64_t factor = 1;
  for (int64_t i = snafu.size() - 1; i >= 0; --i) {
    result += snafu[i] * factor;
    factor *= 5;
  }
  return result;
}

std::deque<int16_t> lltosnafu(int64_t ll) {
  std::deque<int16_t> base5{};
  while (ll > 0) {
    base5.push_front(ll % 5);
    ll /= 5;
  }

  // Add two to every digit in base5.
  // After this step the result might be invalid, so do correction.
  int64_t digits_before_fix = base5.size();
  for (auto &member : base5) {
    member += 2;
  }

  // The correction is to carry any overflow to the next digit.
  // Note that this never produces anything greater than 1 for digits
  // created by overflow.
  for (int64_t i = base5.size() - 1; i >= 0; --i) {
    if (base5[i] > 4) {
      if (i == 0) {
        base5.push_front(0);
        ++i;
      }
      base5[i - 1] += base5[i] / 5;
      base5[i] = base5[i] % 5;
    }
  }

  for (int64_t i = base5.size() - 1;
       i >= (int64_t)(base5.size() - digits_before_fix); --i) {
    base5[i] = base5[i] - 2;
  }

  return base5;
}

std::deque<int16_t> parse_snafu(std::string const &str) {
  std::deque<int16_t> result{};
  for (char c : str) {
    switch (c) {
    case '2':
      result.push_back(2);
      break;
    case '1':
      result.push_back(1);
      break;
    case '0':
      result.push_back(0);
      break;
    case '-':
      result.push_back(-1);
      break;
    case '=':
      result.push_back(-2);
      break;
    }
  }
  return result;
}

std::string print_snafu(std::deque<int16_t> const &snafu) {
  std::ostringstream result{};
  for (int16_t i : snafu) {
    switch (i) {
    case 2:
      result << '2';
      break;
    case 1:
      result << '1';
      break;
    case 0:
      result << '0';
      break;
    case -1:
      result << '-';
      break;
    case -2:
      result << '=';
      break;
    }
  }
  return result.str();
}

int main() {
  int64_t sum = 0;
  std::string line;
  while (std::getline(std::cin, line)) {
    auto parsed = parse_snafu(line);
    int64_t line_res = snafutoll(parsed);
    std::cout << "ln : " << line << " -> " << line_res << std::endl;
    sum += line_res;
    std::cout << "sum: " << sum << " -> " << print_snafu(lltosnafu(sum))
              << std::endl;
  }
}
