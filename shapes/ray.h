#ifndef RAY_H
#define RAY_H
#include "IShape.h"
#include "point.h"
#include "vector.h"

namespace geometry {
struct Ray : IShape {
  Ray(Point s, Point other);
  Ray(Point s, Vector vector);

  Point start;
  Vector v;

  IShape& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif
