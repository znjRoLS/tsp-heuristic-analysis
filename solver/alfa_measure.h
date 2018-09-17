#pragma once

#include <memory>
#include "square_matrix.h"

using std::shared_ptr;

namespace TSP {

  shared_ptr<SquareMatrix<double>> AlfaMeasure(shared_ptr<SquareMatrix<double>> measure_, int special_node);

} // namespace TSP
