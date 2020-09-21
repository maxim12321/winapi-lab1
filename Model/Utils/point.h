#ifndef UTILS_POINT_H_
#define UTILS_POINT_H_

#include <cmath>

struct IntPoint {
  int x, y;
};

struct Point {
  double x, y;

  double Length() const;

  Point operator+(const Point& other) const;
  Point operator-(const Point& other) const;
  Point operator*(double value) const;
  Point operator/(double value) const;

  IntPoint ToInt() const;
};

#endif  // UTILS_POINT_H_
