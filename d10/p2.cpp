#include <cstdint>
#include <deque>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

void do_cycle_draw(int64_t cycle, int64_t x) {
  int64_t cursor = (cycle - 1) % 40;
  if (x - 1 <= cursor && cursor <= x + 1) {
    std::cout << '#';
  } else {
    std::cout << '.';
  }

  if (cursor == 0) {
    std::cout << std::endl;
  }
}
int main() {
  std::set<int64_t> relevant{20, 60, 100, 140, 180, 220};
  std::string instr;
  int64_t val;
  int64_t x = 1;
  int64_t cycle = 1;
  while (std::cin >> instr) {
    if (instr == "addx") {
      std::cin >> val;
      // next cycle is also consumed by add so skip one. (not forgoing the
      // check)
      do_cycle_draw(cycle, x);
      cycle++;
      do_cycle_draw(cycle, x);
      x += val;
      cycle++;
    } else if (instr == "noop") {
      do_cycle_draw(cycle, x);
      cycle++;
    } else {
      std::cout << "invalid: " << instr << std::endl;
      continue;
    }
  }
}
