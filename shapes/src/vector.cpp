#include "../vector.h"

namespace geometry {

Vector::Vector(int64_t x, int64_t y) : x(x), y(y) {
}

int64_t Vector::VectorProduct(const Vector& v) const {
  return this->x * v.y - this->y * v.x;
}

int64_t Vector::DotProductOfVectors(const Vector& v) const {
  return this->x * v.x + this->y * v.y;
}

Vector operator+(const Vector& v) {
  return v;
}

Vector operator-(const Vector& v) {
  return {-v.x, -v.y};
}

Vector operator+(const Vector& v1, const Vector& v2) {
  return {v1.x + v2.x, v1.y + v2.y};
}

Vector operator-(const Vector& v1, const Vector& v2) {
  return {v1.x - v2.x, v1.y - v2.y};
}

Vector operator*(const Vector& v1, const int64_t& n) {
  return {v1.x * n, v1.y * n};
}

Vector operator/(const Vector& v1, const int64_t& n) {
  return {v1.x / n, v1.y / n};
}

Vector& operator+=(Vector& lhs, const Vector& rhs) {
  lhs.x += rhs.x;
  lhs.y += rhs.y;
  return lhs;
}

Vector& operator-=(Vector& lhs, const Vector& rhs) {
  lhs.x -= rhs.x;
  lhs.y -= rhs.y;
  return lhs;
}

Vector& operator*=(Vector& lhs, const int64_t& n) {
  lhs.x *= n;
  lhs.y *= n;
  return lhs;
}

Vector& operator/=(Vector& lhs, const int64_t& n) {
  lhs.x /= n;
  lhs.y /= n;
  return lhs;
}

bool operator==(const Vector& v1, const Vector& v2) {
  return v1.x == v2.x && v2.y == v1.y;
}

Vector operator-(const Point& p1, const Point& p2) {
  return Vector(p1.x - p2.x, p1.y - p2.y);
}
}  // namespace geometry