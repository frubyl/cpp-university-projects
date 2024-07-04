#include <utility>

#include "../polygon.h"
#include "../point.h"
#include "../ray.h"
#include "../segment.h"

namespace geometry {

Polygon::Polygon(std::vector<Point> v) : points(std::move(v)) {
}

IShape& Polygon::Move(const Vector& v) {
  for (size_t i = 0; i < points.size(); i++) {
    points[i].Move(v);
  }
  return *this;
}

bool Polygon::ContainsPoint(const Point& p) const {
  bool ans = false;
  for (size_t i = 0, j = points.size() - 1; i < points.size(); j = i++) {
    if (p.CrossesSegment(Segment(points[i], points[j]))) {
      return true;
    }
    if ((points[i].y > p.y) != (points[j].y > p.y)) {
      double intersect_or_not = static_cast<double>(points[j].x - points[i].x) *
                                    static_cast<double>(p.y - points[i].y) /
                                    static_cast<double>(points[j].y - points[i].y) +
                                static_cast<double>(points[i].x);
      if (static_cast<double>(p.x) < intersect_or_not) {
        ans = !ans;
      }
    }
  }
  return ans;
}

bool Polygon::CrossesSegment(const Segment& s) const {
  for (size_t i = 0; i < points.size() - 1; i++) {
    Segment curr = Segment(points[i], points[i + 1]);
    if (curr.CrossesSegment(s)) {
      return true;
    }
  }
  return false;
}

std::unique_ptr<IShape> Polygon::Clone() const {
  std::unique_ptr<IShape> copy = std::make_unique<Polygon>(points);
  return copy;
}

std::string Polygon::ToString() const {
  std::string ans = "Polygon(";
  for (size_t i = 0; i < points.size() - 1; i++) {
    ans += points[i].ToString() + ", ";
  }
  ans += points[points.size() - 1].ToString() + ")";
  return ans;
}
}  // namespace geometry