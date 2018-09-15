#pragma once

#include <vector>

using std::vector;

class DisjointSet {
 public:
  int _n;
  vector<int> _parent;
  vector<int> _children;

  explicit DisjointSet(int n);

  void Merge(int a, int b);

  bool SameSet(int a, int b);

  int GetParent(int i);
};