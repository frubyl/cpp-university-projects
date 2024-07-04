#include <utility>

#include "../segment.h"
#include "../line.h"

namespace geometry {

Segment::Segment(Point x, Point y) : p1(std::move(x)), p2(std::move(y)) {
}

IShape& Segment::Move(const Vector& v) {
  p1.Move(v);
  p2.Move(v);
  return *this;
}

bool Segment::ContainsPoint(const Point& p) const {
  Line segment_to_line = Line(p1, p2);
  return std::min(p1.x, p2.x) <= p.x && p.x <= std::max(p1.x, p2.x) && std::min(p1.y, p2.y) <= p.y &&
         p.y <= std::max(p1.y, p2.y) && segment_to_line.ContainsPoint(p);
}

bool Segment::CrossesSegment(const Segment& s) const {
  Line this_segment_to_line = Line(p1, p2);
  Line other_segment_to_line = Line(s.p1, s.p2);
  if (this_segment_to_line == other_segment_to_line) {
    return s.ContainsPoint(this->p1) || s.ContainsPoint(this->p2) || this->ContainsPoint(s.p1) ||
           this->ContainsPoint(s.p2);
  }
  return this_segment_to_line.CrossesSegment(s) && other_segment_to_line.CrossesSegment(*this);
}

std::unique_ptr<IShape> Segment::Clone() const {
  std::unique_ptr<IShape> copy = std::make_unique<Segment>(p1, p2);
  return copy;
}

std::string Segment::ToString() const {
  return "Segment(" + p1.ToString() + ", " + p2.ToString() + ")";
}
}  // namespace geometry