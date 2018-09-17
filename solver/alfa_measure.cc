#include "alfa_measure.h"

#include <memory>
#include "mst.h"
#include "container_contains.h"
#include <queue>

using std::make_shared;
using std::max;
using std::queue;

namespace TSP {

shared_ptr<SquareMatrix<double>> AlfaMeasure(shared_ptr<SquareMatrix<double>> measure_, int special_node) {

  int n = measure_->Size().first;

  auto min1tree = MST::Min1Tree(measure_, special_node);

  // this is actually beta for now
  auto alfa = make_shared<SquareMatrix<double>>(n);

  for (int i = 0; i < n ; i ++) {
    (*alfa)[i][i] = 0;
  }

  double longer_special_node_edge = 0;
  vector<int> connected_special_nodes;
  for (auto& edge : min1tree) {
    if (edge.first == special_node) {
      connected_special_nodes.push_back(edge.second);
      longer_special_node_edge = max(longer_special_node_edge, (*measure_)[edge.first][edge.second]);
    } else if (edge.second == special_node) {
      connected_special_nodes.push_back(edge.first);
      longer_special_node_edge = max(longer_special_node_edge, (*measure_)[edge.first][edge.second]);
    }
  }

  for (int j = 0 ; j < n ; j ++) {
    if (j == special_node) continue;
    if (j == connected_special_nodes[0] || j == connected_special_nodes[1]) {
      (*alfa)[special_node][j] = (*alfa)[j][special_node] = 0;
    } else {
      (*alfa)[special_node][j] = (*alfa)[j][special_node] = (*measure_)[special_node][j] - longer_special_node_edge;
    }
  }

  vector<vector<int>> edges(n);

  for (auto& edge : min1tree) {
    if (edge.first == special_node || edge.second == special_node) continue;

    edges[edge.first].push_back(edge.second);
    edges[edge.second].push_back(edge.first);
  }

  for (int root_node = 0 ; root_node < n; root_node ++) {
    if (root_node == special_node) continue;

    vector<bool> visited(n, false);
    visited[root_node] = true;

    vector<double> beta(n, 0);

    queue<int> bfs;

    for (int first_level_node : edges[root_node]) {
      bfs.push(first_level_node);
      visited[first_level_node] = true;
      beta[first_level_node] = (*measure_)[root_node][first_level_node];
    }

    while (!bfs.empty()) {
      int curr_node = bfs.front();
      bfs.pop();

      for (int child : edges[curr_node]) {
        if (visited[child]) continue; // skip parent

        bfs.push(child);
        visited[child] = true;

        beta[child] = max(beta[curr_node], (*measure_)[child][curr_node]);
        (*alfa)[root_node][child] = (*alfa)[child][root_node] = (*measure_)[root_node][child] - beta[child];
      }
    }
  }

  return alfa;
}

}
