#include "util.h"

namespace TSP {

Path GetPathFromEdgeSet(unordered_set<pair<int, int>> edge_set) {
  vector<vector<int>> edges(edge_set.size());
  Path current_path;

  for (pair<int, int> edge : edge_set) {
    edges[edge.second].push_back(edge.first);
    edges[edge.first].push_back(edge.second);
  }

  current_path.push_back(0);

  vector<bool> used(edges.size(), false);
  used[0] = true;

  while (current_path.size() != edges.size()) {
    int last_edge = *current_path.rbegin();

    if (used[edges[last_edge][0]]) {
      current_path.push_back(edges[last_edge][1]);
      used[edges[last_edge][1]] = true;
    } else {
      current_path.push_back(edges[last_edge][0]);
      used[edges[last_edge][0]] = true;
    }
  }

  current_path.push_back(0);

  return current_path;
}

} // namespace TSP
