#include <utility>

#include "../ray.h"
#include "../line.h"
#include "../segment.h"

namespace geometry {

Ray::Ray(Point s, Point other) : start(s), v(other - s) {
}

Ray::Ray(Point s, Vector vector) : start(std::move(s)), v(vector) {
}

IShape& Ray::Move(const Vector& vector) {
  start.Move(vector);
  return *this;
}

bool Ray::ContainsPoint(const Point& p) const {
  Vector start_p = p - start;
  return v.DotProductOfVectors(start_p) >= 0 && v.VectorProduct(start_p) == 0;
}

bool Ray::CrossesSegment(const Segment& s) const {
  if (this->ContainsPoint(s.p1) || this->ContainsPoint(s.p2)) {
    return true;
  }
  Line this_ray = Line(start, Point(start.x + v.x, start.y + v.y));
  Vector p1_start = start - s.p1;
  Vector this_segment = s.p1 - s.p2;
  return this_ray.CrossesSegment(s) && p1_start.VectorProduct(this_segment) * v.VectorProduct(this_segment) < 0;
}

std::unique_ptr<IShape> Ray::Clone() const {
  std::unique_ptr<IShape> copy = std::make_unique<Ray>(start, v);
  return copy;
}

std::string Ray::ToString() const {
  return "Ray(" + start.ToString() + ", Vector(" + std::to_string(v.x) + ", " + std::to_string(v.y) + "))";
}
}  // namespace geometry