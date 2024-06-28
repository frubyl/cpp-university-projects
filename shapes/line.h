#ifndef LINE_H
#define LINE_H
#include "IShape.h"
#include "point.h"
#include "ray.h"

namespace geometry {

struct Line : IShape {
  Line(Point a, Point b);

  int64_t A;
  int64_t B;
  int64_t C;

  Point p1;
  Point p2;

  IShape& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};

bool operator==(Line&, Line&);
}  // namespace geometry
#endif  // LINE_H
