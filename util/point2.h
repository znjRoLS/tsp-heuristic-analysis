#pragma once

struct Point2 {
  double abs();

  double dist_to(Point2 &other);

  Point2 operator-(Point2 &other);

  double x_;
  double y_;
};
