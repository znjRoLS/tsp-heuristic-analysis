#pragma once

#include <memory>

#include "util.h"
#include "square_matrix.h"
#include "point2.h"

using std::shared_ptr;

namespace TSP {

enum WorldType {
//  ASSYMETRIC,
//  SYMMETRIZSAC,
      EUCLIDEAN2D,
//  EUCLIDEAN3D,
};

struct World {
  const int size;
  const WorldType world_type_;
  const shared_ptr<SquareMatrix<double>> distances_;
  const shared_ptr<Nodes2> nodes_;
};

} // namespace TSP
