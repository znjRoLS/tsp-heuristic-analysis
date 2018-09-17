#pragma once

#include <unordered_set>
#include "square_matrix.h"
#include "pair_hash.h"
#include <memory>

using std::unordered_set;
using std::pair;
using std::shared_ptr;

typedef pair<int, int> Edge;
typedef unordered_set<Edge> EdgeSet;

namespace MST {
  EdgeSet Calculate(shared_ptr<SquareMatrix<double>>& distances, int excluded_node = -1);

  pair<Edge, Edge> NearestNodesEdges(const shared_ptr<SquareMatrix<double>>& distances, int node);

  EdgeSet Min1Tree(const shared_ptr<SquareMatrix<double>>& distances, int special_node);

};
