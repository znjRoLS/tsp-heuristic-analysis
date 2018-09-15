#include "mst.h"

#include <map>
#include "disjoint_set.h"

using std::map;

unordered_set<pair<int, int>> MST::Calculate(SquareMatrix<double> distances) {
  int n = distances.size().first;
  DisjointSet disjoint_set(n);

  map<double, pair<int,int>> edges;

  for (int i = 0; i < n; i++) {
    for (int j = i+1 ; j < n; j ++) {
      edges.insert({distances[i][j], {i, j}});
    }
  }

  unordered_set<pair<int,int>> chosen_edges;

  while(chosen_edges.size() != n-1) {
    auto& edge = edges.begin()->second;

    if (!disjoint_set.SameSet(edge.first, edge.second)) {
      disjoint_set.Merge(edge.first, edge.second);

      chosen_edges.insert(edge);
    }

    edges.erase(edges.begin());
  }

  return chosen_edges;
}
