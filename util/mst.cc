#include "mst.h"

#include <map>
#include "disjoint_set.h"
#include <limits>

using std::numeric_limits;
using std::multimap;

namespace MST {

// Note: if excluded_node == -1, no node is excluded
//EdgeSet Calculate(const shared_ptr<SquareMatrix<double>> &distances, int excluded_node = -1) {
//  int n = distances->Size().first;
//  DisjointSet disjoint_set(n);
//
//  multimap<double, pair<int, int>> edges;
//
//  for (int i = 0; i < n; i++) {
//    if (i == excluded_node) continue;
//    for (int j = i + 1; j < n; j++) {
//      if (j == excluded_node) continue;
//      edges.insert({(*distances)[i][j], {i, j}});
//    }
//  }
//
//  EdgeSet chosen_edges;
//
//  while (static_cast<int>(chosen_edges.size()) != (excluded_node == -1 ? n - 1 : n - 2)) {
//    auto &edge = edges.begin()->second;
//
//    if (!disjoint_set.SameSet(edge.first, edge.second)) {
//      disjoint_set.Merge(edge.first, edge.second);
//
//      chosen_edges.insert(edge);
//    }
//
//    edges.erase(edges.begin());
//  }
//
//  return chosen_edges;
//}

EdgeSet Calculate(const shared_ptr<SquareMatrix<double>> &distances, int excluded_node = -1) {
  unsigned n = distances->Size().first;
  EdgeSet chosen_edges;

  int curr_node = (excluded_node + 1) % n;
  vector<int> current_short_edges(n);
  vector<double> current_closest(n);
  vector<bool> visited(n, false);
  visited[curr_node] = true;
  if (excluded_node != -1) {
    visited[excluded_node] = true;
  }

  for (unsigned i = 0; i < n ; i ++) {
    if (visited[i]) continue;
    current_short_edges[i] = curr_node;
    current_closest[i] = (*distances)[curr_node][i];
  }

  unsigned max_num = n-1;
  if (excluded_node != -1) max_num --;
  while (chosen_edges.size() != max_num) {
    int curr_min = -1;
    for (unsigned i = 0; i < n; i ++) {
      if (visited[i]) continue;
      if (curr_min == -1 || current_closest[i] < current_closest[curr_min]) {
        curr_min = i;
      }
    }

    chosen_edges.insert({current_short_edges[curr_min], curr_min});
    visited[curr_min] = true;

    for (unsigned i = 0 ; i < n; i ++) {
      if (visited[i]) continue;
      if ((*distances)[curr_min][i] < current_closest[i]) {
        current_closest[i] = (*distances)[curr_min][i];
        current_short_edges[i] = curr_min;
      }
    }
  }

  return chosen_edges;
}

pair<Edge, Edge> NearestNodesEdges(const shared_ptr<SquareMatrix<double>> &distances, int node) {
  int n = distances->Size().first;

  double min_weight = numeric_limits<double>::max();
  double second_min_weight = numeric_limits<double>::max();

  int min_node = node;
  int second_min_node = node;

  for (int i = 0; i < n; i++) {
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

EdgeSet Min1Tree(const shared_ptr<SquareMatrix<double>> &distances, const int special_node) {

  EdgeSet mst = Calculate(distances, special_node);

  pair<Edge, Edge> additional_edges = NearestNodesEdges(distances, special_node);

  mst.insert(additional_edges.first);
  mst.insert(additional_edges.second);

  return mst;
}

int BestLeaf(const shared_ptr<SquareMatrix<double>> &distances, EdgeSet &mst) {
  int n = distances->Size().first;
  vector<int> degrees(n, 0);

  for (auto &edge : mst) {
    degrees[edge.first]++;
    degrees[edge.second]++;
  }

  int largest_second_neighbour_node = -1;
  double largest_second_neighbour = 0.0;

  for (int i = 0; i < n; i++) {
    if (degrees[i] == 1) {
      auto edge_pair = NearestNodesEdges(distances, i);
      double second_neighbour = (*distances)[edge_pair.second.first][edge_pair.second.second];
      if (second_neighbour > largest_second_neighbour) {
        largest_second_neighbour = second_neighbour;
        largest_second_neighbour_node = i;
      }
    }
  }

  return largest_second_neighbour_node;
}

EdgeSet Min1TreeSetSpecialNode(const shared_ptr<SquareMatrix<double>> &distances, int *special_node) {

  EdgeSet mst = Calculate(distances);

  *special_node = BestLeaf(distances, mst);

  pair<Edge, Edge> additional_edges = NearestNodesEdges(distances, *special_node);
  mst.insert(additional_edges.second);

  return mst;
}

} // namespace MST
