#include "../circle.h"
#include "../point.h"
#include "../segment.h"
#include "../vector.h"
#include <cmath>
#include <utility>

namespace geometry {

Circle::Circle(Point p, int64_t rad) : center(std::move(p)), r(std::move(rad)) {
}

IShape& Circle::Move(const Vector& v) {
  center.Move(v);
  return *this;
}

bool Circle::ContainsPoint(const Point& p) const {
  return ((p.x - center.x) * (p.x - center.x) + (p.y - center.y) * (p.y - center.y)) <= r * r;
}

bool Circle::CrossesSegment(const Segment& s) const {
  Vector v2 = Vector(s.p1 - center);
  Vector v1 = Vector(s.p2 - s.p1);

  double m = v1.DotProductOfVectors(v1);
  double n = v2.DotProductOfVectors(v1) * 2;
  double k = v2.DotProductOfVectors(v2) - r * r;

  double discriminant = n * n - 4 * m * k;
  if (discriminant < 0) {
    return false;
  }
  double r1 = (-n - std::sqrt(discriminant)) / (2.0 * m);
  double r2 = (-n + std::sqrt(discriminant)) / (2.0 * m);
  return (r1 >= 0 && r1 <= 1) || (r2 >= 0 && r2 <= 1);
}

std::unique_ptr<IShape> Circle::Clone() const {
  std::unique_ptr<IShape> copy = std::make_unique<Circle>(center, r);
  return copy;
}

std::string Circle::ToString() const {
  return "Circle(" + center.ToString() + ", " + std::to_string(r) + ")";
}
}  // namespace geometry