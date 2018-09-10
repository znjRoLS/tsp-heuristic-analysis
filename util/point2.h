#pragma once

struct Point2 {
  double abs() const;

  double dist_to(const Point2 &other) const;

  Point2 operator-(const Point2 &other) const;
  Point2 operator+(const Point2 &other) const;

  bool operator==(const Point2 &other) const;
  bool operator!=(const Point2 &other) const;

  double x_;
  double y_;
};
