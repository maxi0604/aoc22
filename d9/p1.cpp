#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <set>
#include <utility>

bool disconnected(int64_t hx, int64_t hy, int64_t tx, int64_t ty) {
  return std::llabs(hx - tx) >= 2 || std::llabs(hy - ty) >= 2;
}
int main() {
  std::set<std::pair<int64_t, int64_t>> tail_positions{{0, 0}};
  int64_t hx = 0, hy = 0;
  int64_t tx = 0, ty = 0;

  char dir;
  int64_t n;

  while (std::cin >> dir >> n) {
    for (int64_t i = 0; i < n; ++i) {
      switch (dir) {
      case 'R':
        ++hx;
        if (disconnected(hx, hy, tx, ty)) {
          ++tx;
          ty = hy;
        }
        break;
      case 'L':
        --hx;
        if (disconnected(hx, hy, tx, ty)) {
          --tx;
          ty = hy;
        }
        break;
      case 'U':
        ++hy;
        if (disconnected(hx, hy, tx, ty)) {
          ++ty;
          tx = hx;
        }
        break;
      case 'D':
        --hy;
        if (disconnected(hx, hy, tx, ty)) {
          --ty;
          tx = hx;
        }
        break;
      }
      tail_positions.insert({tx, ty});
      std::cout << "head: (" << hx << "," << hy << ")";
      std::cout << ", tail: (" << tx << "," << ty << ")";
      std::cout << ", count: " << tail_positions.size() << std::endl;
    }
  }
}
