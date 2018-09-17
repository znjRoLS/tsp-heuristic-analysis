#pragma once

#include <unordered_set>

namespace std {
template<>
struct hash<std::pair<int, int>> {
  inline size_t operator()(const std::pair<int, int> &v) const {
    std::hash<int> int_hasher;
    return int_hasher(v.first) ^ int_hasher(v.second);
  }
};

}