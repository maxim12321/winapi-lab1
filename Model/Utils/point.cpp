#include "point.h"

double Point::Length() const {
  return std::hypot(x, y);
}

Point Point::operator+(const Point& other) const {
  return {x + other.x, y + other.y};
}

Point Point::operator-(const Point& other) const {
  return {x - other.x, y - other.y};
}

Point Point::operator*(double value) const {
  return {x * value, y * value};
}

Point Point::operator/(double value) const {
  return {x / value, y / value};
}

IntPoint Point::ToInt() const {
  return {std::lround(x), std::lround(y)};
}
