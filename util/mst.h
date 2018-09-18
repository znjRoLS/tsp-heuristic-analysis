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
EdgeSet Calculate(shared_ptr<SquareMatrix<double>> &distances, int excluded_node = -1);

pair<Edge, Edge> NearestNodesEdges(const shared_ptr<SquareMatrix<double>> &distances, int node);

EdgeSet Min1Tree(const shared_ptr<SquareMatrix<double>> &distances, int special_node);

int BestLeaf(const shared_ptr<SquareMatrix<double>> &distances, EdgeSet &mst);

//   - The special node for the 1-tree computations is not fixed. A minimum
//       1-tree is determined by computing a minimum spanning tree and then
//       adding an edge corresponding to the second nearest neighbor of one of
//       the leaves of the tree. The leaf chosen is the one that has the longest
//       second nearest neighbor distance.
EdgeSet Min1TreeSetSpecialNode(const shared_ptr<SquareMatrix<double>> &distances, int *special_node);

};
