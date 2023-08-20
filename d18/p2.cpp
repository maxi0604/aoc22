#include <algorithm>
#include <cstdint>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <vector>

int64_t cube_idx(int64_t x, int64_t y, int64_t z, int64_t s) {
  return x + s * y + s * s * z;
}

int64_t to_cube_idx_s(int64_t x, int64_t y, int64_t z, int64_t s) {
  s = s - 2;
  return x + 1 + s * (y + 1) + s * s * (z + 1);
}

int64_t find(std::vector<int64_t> &uf, int64_t a) {
  if (uf[a] == a) {
    return a;
  } else {
    return uf[a] = find(uf, uf[a]);
  }
}
bool unionize(std::vector<int64_t> &uf, int64_t a, int64_t b) {
  a = find(uf, a);
  b = find(uf, b);
  if (a == b)
    return false;

  uf[b] = a;
  return true;
}

void connect_all_to_root(std::vector<int64_t> &uf,
                         std::set<std::tuple<int64_t, int64_t, int64_t>> rock,
                         int64_t rx, int64_t ry, int64_t rz, int64_t s) {
  std::queue<std::tuple<int64_t, int64_t, int64_t>> q{};
  q.push({rx, ry, rz});

  bool first = true;
  while (!q.empty()) {
    auto [tx, ty, tz] = q.front();
    q.pop();

    int64_t top_uf_idx = cube_idx(tx, ty, tz, s);
    if (top_uf_idx >= uf.size()) {
      continue;
    }

    if (rock.count({tx, ty, tz})) {
      continue;
    }

    if (unionize(uf, cube_idx(rx, ry, rz, s), cube_idx(tx, ty, tz, s)) ||
        first) {
      first = false;
      q.push({tx + 1, ty, tz});
      q.push({tx - 1, ty, tz});
      q.push({tx, ty + 1, tz});
      q.push({tx, ty - 1, tz});
      q.push({tx, ty, tz + 1});
      q.push({tx, ty, tz - 1});
    }
  }
}

std::vector<int64_t> init(int64_t n) {
  auto vec = std::vector<int64_t>(n);
  for (int64_t i = 0; i < n; i++) {
    vec[i] = i;
  }
  return vec;
}
int main() {
  std::set<std::tuple<int64_t, int64_t, int64_t>> rock{};
  int64_t xmax = 0, ymax = 0, zmax = 0;

  int64_t x, y, z;
  char comma;
  while (std::cin >> x >> comma >> y >> comma >> z) {
    if (x > xmax)
      xmax = x;
    if (y > ymax)
      ymax = y;
    if (z > zmax)
      zmax = z;
    // shift the rock so that it lies cleanly within the bounding cube.
    rock.insert({x + 1, y + 1, z + 1});
  }

  // bounding cube.
  int64_t bc_size = std::max({xmax, ymax, zmax}) + 3;
  auto uf = init(bc_size * bc_size * bc_size);

  // connect air to "air root" at 0 0 0 outside the cube.
  connect_all_to_root(uf, rock, 0, 0, 0, bc_size);

  int64_t count = 0;
  // for (auto &[x, y, z] : rock) {
  //   if (rock.count({x + 1, y, z}) == 0)
  //     connect_all_to_root(uf, x + 1, y, z, bc_size);
  //   if (rock.count({x - 1, y, z}) == 0)
  //     connect_all_to_root(uf, x - 1, y, z, bc_size);
  //   if (rock.count({x, y + 1, z}) == 0)
  //     connect_all_to_root(uf, x, y + 1, z, bc_size);
  //   if (rock.count({x, y - 1, z}) == 0)
  //     connect_all_to_root(uf, x, y - 1, z, bc_size);
  //   if (rock.count({x, y, z + 1}) == 0)
  //     connect_all_to_root(uf, x, y, z + 1, bc_size);
  //   if (rock.count({x, y, z - 1}) == 0)
  //     connect_all_to_root(uf, x, y, z - 1, bc_size);
  // }

  // Only count surfaces where the exposed surface has been found to be
  // connected to the air block.
  for (auto &[x, y, z] : rock) {
    if (rock.count({x + 1, y, z}) == 0 &&
        find(uf, cube_idx(x + 1, y, z, bc_size)) == find(uf, 0))
      count++;
    if (rock.count({x - 1, y, z}) == 0 &&
        find(uf, cube_idx(x - 1, y, z, bc_size)) == find(uf, 0))
      count++;
    if (rock.count({x, y + 1, z}) == 0 &&
        find(uf, cube_idx(x, y + 1, z, bc_size)) == find(uf, 0))
      count++;
    if (rock.count({x, y - 1, z}) == 0 &&
        find(uf, cube_idx(x, y - 1, z, bc_size)) == find(uf, 0))
      count++;
    if (rock.count({x, y, z + 1}) == 0 &&
        find(uf, cube_idx(x, y, z + 1, bc_size)) == find(uf, 0))
      count++;
    if (rock.count({x, y, z - 1}) == 0 &&
        find(uf, cube_idx(x, y, z - 1, bc_size)) == find(uf, 0))
      count++;
  }
  std::cout << count << std::endl;
}
