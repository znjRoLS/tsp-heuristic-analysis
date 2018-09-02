#include "point2.h"

#include <cmath>

double Point2::abs() {
    return sqrt(x_*x_ + y_*y_);
}

Point2 Point2::operator-(Point2 other) {
    return {x_ - other.x_, y_ - other.y_};
}