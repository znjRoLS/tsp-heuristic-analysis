#include "disjoint_set.h"

#include <algorithm>

using std::swap;

DisjointSet::DisjointSet(int n) : _n(n), _parent(n), _children(n, 0) {
  for (int i = 0; i < n; i++) _parent[i] = i;
}

void DisjointSet::Merge(int a, int b) {
  int pa = GetParent(a);
  int pb = GetParent(b);

  if (_children[pb] > _children[pa]) swap(pa, pb);
  _parent[pb] = pa;
  _children[pa] += _children[pb] + 1;
}

bool DisjointSet::SameSet(int a, int b) {
  return GetParent(a) == GetParent(b);
}

int DisjointSet::GetParent(int i) {
  while (_parent[i] != i) i = _parent[i];
  return i;
}
