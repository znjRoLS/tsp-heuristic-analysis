#include "mst.h"

#include <map>
#include "disjoint_set.h"
#include <limits>

using std::numeric_limits;
using std::map;

namespace MST {

// Note: if excluded_node == -1, no node is excluded
EdgeSet Calculate(const shared_ptr<SquareMatrix<double>>& distances, int excluded_node = -1) {
  int n = distances->Size().first;
  DisjointSet disjoint_set(n);

  map<double, pair<int,int>> edges;

  for (int i = 0; i < n; i++) {
    if (i == excluded_node) continue;
    for (int j = i + 1; j < n; j++) {
      if (j == excluded_node) continue;
      edges.insert({(*distances)[i][j], {i, j}});
    }
  }

  EdgeSet chosen_edges;

  while(static_cast<int>(chosen_edges.size()) != (excluded_node == -1?n-1:n-2)) {
    auto& edge = edges.begin()->second;

    if (!disjoint_set.SameSet(edge.first, edge.second)) {
      disjoint_set.Merge(edge.first, edge.second);

      chosen_edges.insert(edge);
    }

    edges.erase(edges.begin());
  }

  return chosen_edges;
}

pair<Edge, Edge> NearestNodesEdges(const shared_ptr<SquareMatrix<double>>& distances, int node) {
  int n = distances->Size().first;

  double min_weight = numeric_limits<double>::max();
  double second_min_weight = numeric_limits<double>::max();

  int min_node = node;
  int second_min_node = node;

  for (int i = 0; i < n; i ++) {
    if (i == node) continue;

    double dist = (*distances)[node][i];
    if (dist < min_weight) {
      second_min_node = min_node;
      second_min_weight = min_weight;
      min_weight = dist;
      min_node = i;
    } else if (dist < second_min_weight) {
      second_min_weight = dist;
      second_min_node = i;
    }
  }


  return {{node, min_node}, {node, second_min_node}};
}

EdgeSet Min1Tree(const shared_ptr<SquareMatrix<double>>& distances, const int special_node) {

  EdgeSet mst = Calculate(distances, special_node);

  pair<Edge, Edge> additional_edges = NearestNodesEdges(distances, special_node);

  mst.insert(additional_edges.first);
  mst.insert(additional_edges.second);

  return mst;
}

} // namespace MST
