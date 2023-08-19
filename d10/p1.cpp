#include <cstdint>
#include <deque>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
int main() {
  std::set<int64_t> relevant{20, 60, 100, 140, 180, 220};
  std::string instr;
  int64_t val;
  int64_t x = 1;
  int64_t cycle = 1;
  int64_t ss_sum = 0;
  while (std::cin >> instr) {
    if (instr == "addx") {
      std::cin >> val;
      std::cout << "add " << val << std::endl;
      // next cycle is also consumed by add so skip one. (not forgoing the
      // check)
      if (relevant.count(cycle)) {
        ss_sum += cycle * x;
      }
      cycle++;

      if (relevant.count(cycle)) {
        ss_sum += cycle * x;
      }
      x += val;
      cycle++;
    } else if (instr == "noop") {
      if (relevant.count(cycle)) {
        ss_sum += cycle * x;
      }
      cycle++;
    } else {
      std::cout << "invalid: " << instr << std::endl;
      continue;
    }

    std::cout << "cycle = " << cycle << ": x = " << x << " ss = " << cycle * x
              << std::endl;
  }

  std::cout << "signal strength sum: " << ss_sum << std::endl;
}
