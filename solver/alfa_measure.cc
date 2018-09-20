#include "alfa_measure.h"

#include <memory>
#include "mst.h"
#include "container_contains.h"
#include <queue>
#include <limits>
#include "double_compare.h"

using std::numeric_limits;
using std::make_shared;
using std::max;
using std::queue;
using std::min;

namespace TSP {

shared_ptr<SquareMatrix<double>> AlfaMeasure(shared_ptr<SquareMatrix<double>> measure) {

  int n = measure->Size().first;
  int special_node;

  auto min1tree = MST::Min1TreeSetSpecialNode(measure, &special_node);

  // this is actually beta for now
  auto alfa = make_shared<SquareMatrix<double>>(n);

  for (int i = 0; i < n; i++) {
    (*alfa)[i][i] = 0;
  }

  double longer_special_node_edge = 0;
  vector<int> connected_special_nodes;
  for (auto &edge : min1tree) {
    if (edge.first == special_node) {
      connected_special_nodes.push_back(edge.second);
      longer_special_node_edge = max(longer_special_node_edge, (*measure)[edge.first][edge.second]);
    } else if (edge.second == special_node) {
      connected_special_nodes.push_back(edge.first);
      longer_special_node_edge = max(longer_special_node_edge, (*measure)[edge.first][edge.second]);
    }
  }

  for (int j = 0; j < n; j++) {
    if (j == special_node) continue;
    if (j == connected_special_nodes[0] || j == connected_special_nodes[1]) {
      (*alfa)[special_node][j] = (*alfa)[j][special_node] = 0;
    } else {
      (*alfa)[special_node][j] = (*alfa)[j][special_node] = (*measure)[special_node][j] - longer_special_node_edge;
    }
  }

  vector<vector<int>> edges(n);

  for (auto &edge : min1tree) {
    if (edge.first == special_node || edge.second == special_node) continue;

    edges[edge.first].push_back(edge.second);
    edges[edge.second].push_back(edge.first);
  }

  for (int root_node = 0; root_node < n; root_node++) {
    if (root_node == special_node) continue;

    vector<bool> visited(n, false);
    visited[root_node] = true;

    vector<double> beta(n, 0);

    queue<int> bfs;

    for (int first_level_node : edges[root_node]) {
      bfs.push(first_level_node);
      visited[first_level_node] = true;
      beta[first_level_node] = (*measure)[root_node][first_level_node];
    }

    while (!bfs.empty()) {
      int curr_node = bfs.front();
      bfs.pop();

      for (int child : edges[curr_node]) {
        if (visited[child]) continue; // skip parent

        bfs.push(child);
        visited[child] = true;

        beta[child] = max(beta[curr_node], (*measure)[child][curr_node]);
        (*alfa)[root_node][child] = (*alfa)[child][root_node] = (*measure)[root_node][child] - beta[child];
      }
    }
  }

  return alfa;
}


shared_ptr<SquareMatrix<double>> AlfaImprovedMeasure(shared_ptr<SquareMatrix<double>> measure_) {

  shared_ptr<SquareMatrix<double>> new_measure = make_shared<SquareMatrix<double>> (measure_->GetData());

  GetBetterMeasure(new_measure);

  return AlfaMeasure(new_measure);
}

void GetBetterMeasure(shared_ptr<SquareMatrix<double>> measure) {

    int n = measure->Size().first;

    vector<double> pi (n, 0);
    bool initial_increase = true;

    // set first step to minimum edge
    double min_edge = numeric_limits<double>::max();
    for (int i = 0; i < n; i++) {
      for (int j = i+1; j < n; j++) {
        min_edge = min(min_edge, (*measure)[i][j]);
      }
    }
    double t = min_edge;
    int current_period = n/2;
    int current_iter = 0;

    double last_total_weight = 0.0;

    vector<int> last_v (n,0);

    double largest_t = t;

    double value_ = 0;

    const double smallest_t_ratio = 100;
    const double v_intertia = 0.7;

    while (current_period > 0 && largest_t/t < smallest_t_ratio) {

      int current_node;

      EdgeSet min1tree = MST::Min1TreeSetSpecialNode(measure, &current_node);

      double total_weight = 0;
      for (auto &edge : min1tree) {
        total_weight += (*measure)[edge.first][edge.second];
      }

      for (double pi_elem : pi) {
        total_weight -= pi_elem * 2;
      }

      bool w_increase = DOUBLE_GREATER(total_weight, value_);

      if (w_increase) {
        value_ = total_weight;
      }

      bool total_weight_increase = DOUBLE_GREATER(total_weight, last_total_weight);
      last_total_weight = total_weight;

      // updating pi

      vector<int> v(n, -2);

      for (auto &edge : min1tree) {
        v[edge.first]++;
        v[edge.second]++;
      }
      // check found optimal
      bool all_zero = true;
      for (int vi : v) {
        if (vi != 0) all_zero = false;
      }
      if (all_zero) {
        break;
      }

      if (initial_increase && w_increase) {
        t *= 2;
        largest_t *= 2;
      } else {
        initial_increase = false;
      }

      if (!total_weight_increase) {
        current_period = current_iter + (current_period - current_iter) /2;
      }

      // check if period is zero
      if (current_period == current_iter) {
        if (w_increase) {
          current_period *= 2;
        } else {
          current_period /= 2;
          t /= 2;

          current_iter = 0;
        }
      }

      for (int i = 0; i < n; i++) {
        double
            pi_change = t * (last_v[i] * v_intertia + v[i] * (1 - v_intertia));
        pi[i] += pi_change;
        for (int j = 0; j < n; j++) {
          if (i == j) continue;
          (*measure)[i][j] += pi_change;
          (*measure)[j][i] += pi_change;
        }
      }

      last_v = v;

      current_iter++;
    }
}

}
