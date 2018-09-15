#pragma once

#include <unordered_set>
#include "square_matrix.h"
#include "pair_hash.h"

using std::unordered_set;
using std::pair;

class MST {
  unordered_set<pair<int,int>> Calculate(SquareMatrix<double> distances);
};
