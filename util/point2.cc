#include "point2.h"

#include <cmath>

double Point2::abs() {
    return sqrt(x_*x_ + y_*y_);
}