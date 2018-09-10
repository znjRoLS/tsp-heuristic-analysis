#include "point2.h"

#include <cmath>
#include "double_compare.h"

double Point2::abs() const {
  return sqrt(x_ * x_ + y_ * y_);
}

double Point2::dist_to(const Point2 &other) const {
  return (*this - other).abs();
}

Point2 Point2::operator-(const Point2 &other) const {
  return {x_ - other.x_, y_ - other.y_};
}

Point2 Point2::operator+(const Point2 &other) const {
  return {x_ + other.x_, y_ + other.y_};
}
bool Point2::operator==(const Point2 &other) const {
  return DOUBLE_EQUAL(x_, other.x_) && DOUBLE_EQUAL(y_, other.y_);
}
bool Point2::operator!=(const Point2 &other) const {
  return !operator==(other);
}
