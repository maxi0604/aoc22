#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <set>
#include <string>
#include <vector>
class Directory {
public:
  Directory();
  Directory(Directory &&) = default;
  Directory(const Directory &) = default;
  Directory &operator=(Directory &&) = default;
  Directory &operator=(const Directory &) = default;
  ~Directory();

  std::map<std::string, std::shared_ptr<Directory>> child_dirs{};
  std::weak_ptr<Directory> parent{};
  int64_t file_size = 0;
  int64_t acc_size = 0;
  int64_t WalkTree() {
    this->AccSize();
    return this->WalkTreeInternal();
  }

  std::shared_ptr<Directory> walk_into(std::string name,
                                       std::shared_ptr<Directory> cur) {
    if (name == "..") {
      return parent.lock();
    }

    if (!child_dirs[name]) {
      child_dirs[name] = std::make_shared<Directory>();
    }
    child_dirs[name]->parent = cur;
    return child_dirs[name];
  }

  int64_t AccSize() {
    this->acc_size = this->file_size;
    for (auto &child : child_dirs) {
      std::cout << "accsize walking into: " << child.first << std::endl;
      this->acc_size += child.second->AccSize();
    }
    std::cout << "accsize: " << acc_size;
    return this->acc_size;
  }

private:
  int64_t WalkTreeInternal() {
    int64_t result = 0;

    std::cout << "res before: " << result << " acc: " << acc_size << std::endl;
    if (this->acc_size <= 100000) {
      result += this->acc_size;
      std::cout << "adding size: " << this->acc_size << std::endl;
    }

    for (auto &child : child_dirs) {
      std::cout << "walking into" << child.first << std::endl;
      result += child.second->WalkTreeInternal();
    }

    return result;
  }
};

Directory::Directory() {}

Directory::~Directory() {}

int main() {
  std::regex cd_rgx("\\$ cd (.+)");
  std::regex file_rgx("(\\d+) .*");
  std::string line;
  std::shared_ptr root = std::make_shared<Directory>();
  std::shared_ptr<Directory> cur = root;
  while (std::getline(std::cin, line)) {
    std::smatch cd_match;
    std::smatch file_match;
    if (std::regex_match(line, cd_match, cd_rgx)) {
      if (cd_match[1] == "/") {
        cur = root;
      } else {
        cur = cur->walk_into(cd_match[1], cur);
      }
      continue;
    } else if (line == "$ ls") {
      continue;
    } else if (std::regex_match(line, file_match, file_rgx)) {
      int64_t fsize = std::stoll(file_match[1]);
      cur->file_size += fsize;
    }
  }

  std::cout << root->WalkTree() << std::endl;
}
