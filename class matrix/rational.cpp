#include <numeric>
#include "rational.h"

void Rational::Normalize(int &n, int &d) {
  if (d <= 0) {
    if (d == 0) {
      throw RationalDivisionByZero{};
    }
    n = -n;
    d = -d;
  }
  int shortener = std::gcd(n, d);
  n /= shortener;
  d /= shortener;
}

Rational::Rational() : Rational(0)
{ }

Rational::Rational(int n) {
  numerator_ = n;
  denominator_ = 1;
}

Rational::Rational(int n, int d) {
  Normalize(n, d);
  numerator_ = n;
  denominator_ = d;
}

int Rational::GetNumerator() const {
  return numerator_;
}

int Rational::GetDenominator() const {
  return denominator_;
}

void Rational::SetNumerator(int n) {
  Normalize(n, denominator_);
  numerator_ = n;
}

void Rational::SetDenominator(int d) {
  Normalize(numerator_, d);
  denominator_ = d;
}

Rational Rational::operator*(Rational multiplier) const {
  int n1 = numerator_;
  int d1 = denominator_;
  int n2 = multiplier.numerator_;
  int d2 = multiplier.denominator_;
  Normalize(n1, d2);
  Normalize(n2, d1);
  return {n1 * n2, d1 * d2};
}

Rational Rational::operator+(Rational summand) const {
  int n = numerator_ * summand.denominator_ + summand.numerator_ * denominator_;
  int d = denominator_ * summand.denominator_;
  Normalize(n, d);
  return {n, d};
}

Rational Rational::operator-(Rational deductible) const {
  int n = numerator_ * deductible.denominator_ - deductible.numerator_ * denominator_;
  int d = denominator_ * deductible.denominator_;
  Normalize(n, d);
  return {n, d};
}

Rational Rational::operator/(Rational divisor) const {
  int n1 = numerator_;
  int d1 = denominator_;
  int n2 = divisor.numerator_;
  int d2 = divisor.denominator_;
  Normalize(n1, n2);
  Normalize(d2, d1);
  return {n1 * d2, d1 * n2};
}

Rational Rational::operator+() const {
  return {numerator_, denominator_};
}

Rational Rational::operator-() const {
  return {-numerator_, denominator_};
}

Rational& Rational::operator++() {
  numerator_ += denominator_;
  return *this;
}

Rational& Rational::operator--() {
  numerator_ -= denominator_;
  return *this;
}

Rational Rational::operator++(int) { // NOLINT(*-dcl21-cpp)
  int n = numerator_;
  numerator_ += denominator_;
  return {n, denominator_};
}

Rational Rational::operator--(int) { // NOLINT(*-dcl21-cpp)
  int n = numerator_;
  numerator_ -= denominator_;
  return {n, denominator_};
}

bool operator<(Rational left, Rational right) {
  return left.GetNumerator() * right.GetDenominator() < right.GetNumerator() * left.GetDenominator();
}

bool operator<=(Rational left, Rational right) {
  return left.GetNumerator() * right.GetDenominator() <= right.GetNumerator() * left.GetDenominator();
}

bool operator>(Rational left, Rational right) {
  return left.GetNumerator() * right.GetDenominator() > right.GetNumerator() * left.GetDenominator();
}

bool operator>=(Rational left, Rational right) {
  return left.GetNumerator() * right.GetDenominator() >= right.GetNumerator() * left.GetDenominator();
}

bool operator==(Rational left, Rational right) {
  return left.GetNumerator() == right.GetNumerator() && left.GetDenominator() == right.GetDenominator();
}

bool operator!=(Rational left, Rational right) {
  return left.GetNumerator() != right.GetNumerator() || left.GetDenominator() != right.GetDenominator();
}

Rational &Rational::operator+=(Rational summand) {
  auto temp = *this + summand;
  numerator_ = temp.numerator_;
  denominator_ = temp.denominator_;
  return *this;
}

Rational &Rational::operator*=(Rational summand) {
  auto temp = *this * summand;
  numerator_ = temp.numerator_;
  denominator_ = temp.denominator_;
  return *this;
}

Rational &Rational::operator/=(Rational summand) {
  auto temp = *this / summand;
  numerator_ = temp.numerator_;
  denominator_ = temp.denominator_;
  return *this;
}

Rational &Rational::operator-=(Rational summand) {
  auto temp = *this - summand;
  numerator_ = temp.numerator_;
  denominator_ = temp.denominator_;
  return *this;
}

std::ostream& operator<<(std::ostream& out_stream, Rational input) {
  out_stream << input.GetNumerator();
  if (input.GetDenominator() != 1) {
    out_stream << '/' << input.GetDenominator();
  }
  return out_stream;
}

std::istream& operator>>(std::istream& in_stream, Rational& output) {
  int n = 0;
  int d = 1;
  in_stream >> n;
  char next_char = 0;
  in_stream.get(next_char);

  if (next_char == '/') {
    int peeked = in_stream.peek();
    if (peeked == '-' || static_cast<unsigned int>(peeked - '0') <= 9) {
      in_stream >> d;
    }
  }

  output = Rational(n, d);
  return in_stream;
}
