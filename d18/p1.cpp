#include <cstdint>
#include <iostream>
#include <set>
#include <tuple>
int main() {
  std::set<std::tuple<int64_t, int64_t, int64_t>> rock{};
  int64_t x, y, z;
  char comma;
  while (std::cin >> x >> comma >> y >> comma >> z) {
    rock.insert({x, y, z});
  }

  int64_t count = 0;
  for (auto &[x, y, z] : rock) {
    if (rock.count({x + 1, y, z}) == 0)
      count++;
    if (rock.count({x - 1, y, z}) == 0)
      count++;
    if (rock.count({x, y + 1, z}) == 0)
      count++;
    if (rock.count({x, y - 1, z}) == 0)
      count++;
    if (rock.count({x, y, z + 1}) == 0)
      count++;
    if (rock.count({x, y, z - 1}) == 0)
      count++;
  }

  std::cout << count << std::endl;
}
