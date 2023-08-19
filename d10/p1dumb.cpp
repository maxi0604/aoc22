#include <cstdint>
#include <deque>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>
int main() {
  std::deque<std::pair<int, int>> pipeline{};
  std::set<int64_t> relevant{20, 60, 100, 140, 180, 220};
  std::string instr;
  int64_t val;
  int64_t x = 1;
  int64_t cycle = 1;
  int64_t ss_sum = 0;
  while (std::cin >> instr) {
    if (instr == "addx") {
      std::cin >> val;
      pipeline.push_back({1, val});
      std::cout << "add " << val << std::endl;
    } else if (instr != "noop") {
      std::cout << "invalid: " << instr << std::endl;
      continue;
    }

    std::cout << "cycle = " << cycle << ": x = " << x << " ss = " << cycle * x
              << std::endl;
    if (relevant.count(cycle)) {
      ss_sum += cycle * x;
    }

    for (auto it = pipeline.begin(); it != pipeline.end();) {
      if (it->first == 0) {
        x += it->second;
        it = pipeline.erase(it);
      } else {
        (it->first)--;
        it++;
      }
    }

    cycle++;
  }

  std::cout << "signal strength sum: " << ss_sum << std::endl;
}
