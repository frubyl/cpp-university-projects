#ifndef CIRCLE_H
#define CIRCLE_H
#include "IShape.h"
#include "point.h"

namespace geometry {
struct Circle : IShape {
  Circle(Point p, int64_t rad);

  Point center;
  int64_t r;

  IShape& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif
