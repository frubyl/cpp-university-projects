#ifndef POINT_H
#define POINT_H
#include "IShape.h"

namespace geometry {

struct Point : IShape {
  Point(int64_t x, int64_t y);

  int64_t x;
  int64_t y;

  IShape& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif
