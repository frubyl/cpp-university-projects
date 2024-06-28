#ifndef SEGMENT_H
#define SEGMENT_H
#include "point.h"

namespace geometry {

struct Segment : IShape {
  Segment(Point x, Point y);

  Point p1;
  Point p2;

  IShape& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif  // SEGMENT_H
