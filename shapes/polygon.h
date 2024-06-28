#ifndef POLYGON_H
#define POLYGON_H
#include "IShape.h"
#include <vector>

namespace geometry {
struct Polygon : IShape {
  explicit Polygon(std::vector<Point>);

  std::vector<Point> points;

  IShape& Move(const Vector&) override;
  bool ContainsPoint(const Point&) const override;
  bool CrossesSegment(const Segment&) const override;
  std::unique_ptr<IShape> Clone() const override;
  std::string ToString() const override;
};
}  // namespace geometry
#endif
