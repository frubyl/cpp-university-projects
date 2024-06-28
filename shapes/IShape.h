#ifndef ISHAPE_H
#define ISHAPE_H
#include <memory>
#include <string>

namespace geometry {

struct Point;
struct Vector;
struct Segment;

struct IShape {
  virtual ~IShape() = default;

  virtual IShape& Move(const Vector&) = 0;
  virtual bool ContainsPoint(const Point&) const = 0;
  virtual bool CrossesSegment(const Segment&) const = 0;
  virtual std::unique_ptr<IShape> Clone() const = 0;
  virtual std::string ToString() const = 0;
};
}  // namespace geometry
#endif  // ISHAPE_H
