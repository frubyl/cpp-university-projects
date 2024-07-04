#include "../point.h"
#include "../segment.h"
#include "../vector.h"

namespace geometry {

Point::Point(int64_t x, int64_t y) : x(x), y(y) {
}

IShape& Point::Move(const Vector& v) {
  x += v.x;
  y += v.y;
  return *this;
}

bool Point::ContainsPoint(const Point& point) const {
  return x == point.x && y == point.y;
}

bool Point::CrossesSegment(const Segment& s) const {
  return s.ContainsPoint(*this);
}

std::unique_ptr<IShape> Point::Clone() const {
  std::unique_ptr<IShape> copy = std::make_unique<Point>(x, y);
  return copy;
}

std::string Point::ToString() const {
  return "Point(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}
}  // namespace geometry