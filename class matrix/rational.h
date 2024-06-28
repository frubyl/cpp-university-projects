#ifndef RATIONAL_RATIONAL_H_
#define RATIONAL_RATIONAL_H_

#include <istream>
#include <stdexcept>

class RationalDivisionByZero : public std::runtime_error {
 public:
  RationalDivisionByZero() : std::runtime_error("RationalDivisionByZero") {
  }
};

class Rational {
 public:
  Rational();
  Rational(int n); // NOLINT
  Rational(int n, int d);
  int GetNumerator() const; // NOLINT(*-use-nodiscard)
  int GetDenominator() const; // NOLINT(*-use-nodiscard)
  void SetNumerator(int n);
  void SetDenominator(int d);
  Rational operator+(Rational summand) const;
  Rational operator-(Rational deductible) const;
  Rational operator/(Rational divisor) const;
  Rational operator*(Rational multiplier) const;
  Rational operator+() const;
  Rational operator-() const;
  Rational& operator++(); // prefix
  Rational operator++(int); // NOLINT(*-dcl21-cpp)
  Rational& operator--();
  Rational operator--(int); // NOLINT(*-dcl21-cpp)
  Rational& operator+=(Rational summand);
  Rational& operator-=(Rational summand);
  Rational& operator*=(Rational summand);
  Rational& operator/=(Rational summand);

 private:
  int numerator_;
  int denominator_;
  static void Normalize(int &n, int& d);
};

bool operator<(Rational left, Rational right);
bool operator<=(Rational left, Rational right);
bool operator>(Rational left, Rational right);
bool operator>=(Rational left, Rational right);
bool operator==(Rational left, Rational right);
bool operator!=(Rational left, Rational right);

std::istream& operator>>(std::istream& in_stream, Rational &output);

std::ostream& operator<<(std::ostream& out_stream, Rational input);

#endif //RATIONAL_RATIONAL_H_
