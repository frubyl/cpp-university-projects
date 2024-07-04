#include "../line.h"
#include "../point.h"
#include "../vector.h"
#include "../segment.h"

namespace geometry {

Line::Line(Point a, Point b) : p1(std::move(a)), p2(std::move(b)) {
  C = p1.x * p2.y - p2.x * p1.y;
  B = p2.x - p1.x;
  A = p1.y - p2.y;
}

IShape& Line::Move(const Vector& v) {
  p1.Move(v);
  p2.Move(v);

  C = p1.x * p2.y - p2.x * p1.y;
  B = p2.x - p1.x;
  A = p1.y - p2.y;
  return *this;
}

bool Line::ContainsPoint(const Point& p) const {
  return A * p.x + B * p.y + C == 0;
}

bool Line::CrossesSegment(const Segment& s) const {
  int64_t first_expression = A * s.p1.x + B * s.p1.y + C;
  int64_t second_expression = A * s.p2.x + B * s.p2.y + C;

  return first_expression * second_expression <= 0;
}

std::unique_ptr<IShape> Line::Clone() const {
  std::unique_ptr<IShape> copy = std::make_unique<Line>(p1, p2);
  return copy;
}

std::string Line::ToString() const {
  return "Line(" + std::to_string(A) + ", " + std::to_string(B) + ", " + std::to_string(C) + ")";
}

bool operator==(Line& l1, Line& l2) {
  return l1.ContainsPoint(l2.p1) && l1.ContainsPoint(l2.p2);
}
}  // namespace geometry
