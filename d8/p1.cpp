#include <algorithm>
#include <array>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

int main() {
  std::vector<std::string> grid;
  std::vector<std::vector<bool>> seen;

  std::string line;
  while (std::getline(std::cin, line)) {
    grid.push_back(line);
    seen.push_back(std::vector<bool>(line.length()));
  }
  std::cout << "done parsing" << std::endl;

  std::vector<std::tuple<int, int, int, int, bool>> dirs{
      // dx, dy, dstartx, dstarty, start_bot_right
      {0, 1, 1, 0, false},  // down
      {1, 0, 0, 1, false},  // right
      {-1, 0, 0, -1, true}, // left
      {0, -1, -1, 0, true}  // up
  };

  int count = 0;

  for (auto &dir : dirs) {
    const auto [dx, dy, dstartx, dstarty, start_br] = dir;
    std::cout << dx << dy << dstartx << dstarty << start_br << std::endl;
    int64_t initial_x, initial_y;
    if (start_br) {
      initial_x = grid.size() - 1;
      initial_y = grid[0].size() - 1;
    } else {
      initial_x = 0;
      initial_y = 0;
    }

    for (int64_t start_x = initial_x, start_y = initial_y;;
         start_x += dstartx, start_y += dstarty) {

      std::cout << "start: " << start_x << ", " << start_y << std::endl;
      if (start_x < 0 || start_x >= grid.size() || start_y < 0 ||
          start_y >= grid[start_x].size()) {
        std::cout << "nextdir" << std::endl;
        break;
      }
      char min = 0;
      for (int64_t x = start_x, y = start_y;; x += dx, y += dy) {
        std::cout << "(" << x << ", " << y << ")" << std::endl;
        if (x < 0 || x >= grid.size() || y < 0 || y >= grid[x].size()) {
          break;
        }
        char cur = grid[x][y];
        if (cur > min) {
          if (!seen[x][y]) {
            ++count;
          }
          seen[x][y] = true;
          min = cur;
        }
      }
    }
    std::cout << count << std::endl;
  }
}
