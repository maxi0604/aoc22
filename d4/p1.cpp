#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

bool a_contains_b(int64_t a1, int64_t a2, int64_t b1, int64_t b2) {
  if (a1 > a2)
    std::swap(a1, a2);

  if (b1 > b2)
    std::swap(b1, b2);

  return a1 <= b1 && b2 <= a2;
}

int main() {
  int64_t a1, a2, b1, b2;
  char spam;
  int64_t count = 0;
  while (std::cin >> a1 >> spam >> a2 >> spam >> b1 >> spam >> b2) {
    if (a_contains_b(a1, a2, b1, b2) || a_contains_b(b1, b2, a1, a2)) {
      count++;
      std::cout << a1 << ", " << a2 << " in " << b1 << ", " << b2
                << " or vice versa" << std::endl;
    }
  }

  std::cout << count;
}
