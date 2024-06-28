#ifndef VECTOR_H
#define VECTOR_H
#include <cstdint>
#include "point.h"

namespace geometry {

struct Vector {
  Vector(int64_t x, int64_t y);

  int64_t x;
  int64_t y;

  int64_t VectorProduct(const Vector&) const;
  int64_t DotProductOfVectors(const Vector&) const;

  friend Vector& operator+=(Vector& lhs, const Vector& rhs);
  friend Vector& operator-=(Vector& lhs, const Vector& rhs);
  friend Vector& operator*=(Vector& lhs, const int64_t& n);
  friend Vector& operator/=(Vector& lhs, const int64_t& n);
};

Vector operator+(const Vector& v);
Vector operator-(const Vector& v);

Vector operator+(const Vector& v1, const Vector& v2);
Vector operator-(const Vector& v1, const Vector& v2);
Vector operator*(const Vector& v1, const int64_t& n);
Vector operator/(const Vector& v1, const int64_t& n);
Vector operator-(const Point& p1, const Point& p2);

bool operator==(const Vector& v1, const Vector& v2);
}  // namespace geometry
#endif
