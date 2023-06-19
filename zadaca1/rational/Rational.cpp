#include "Rational.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>

// formatiranje nekih vrijednosti kao stringa, posredik stringa i objekta,
// parsiranje stringa, stringstream i getline
// implementacija gcd
int gcd(int numerator, int denominator) {
  int num = abs(numerator);
  int denom = abs(denominator);
  int shift;
  for (shift = 0; ((num | denom) & 1) == 0; ++shift) {
    num >>= 1;
    denom >>= 1;
  }
  while ((num & 1) == 0) {
    num >>= 1;
  }
  while (denom != 0) {
    while ((denom & 1) == 0) {
      denom >>= 1;
    }
    if (num > denom) {
      std::swap(num, denom);
    }
    denom -= num;
  }
  return num << shift;
}

void Rational::skrati() {
  int this_gcd = gcd(numerator_, denominator_);
  if (this_gcd != 1 && this_gcd != 0) {
    numerator_ /= this_gcd;
    denominator_ /= this_gcd;
  }
}

void Rational::predznak() {
  if (denominator_ < 0) {
    denominator_ *= -1;
    numerator_ *= -1;
  }
}

Rational::Rational() {}

Rational::Rational(int numerator, int denominator) {
  if (!denominator)
    throw std::invalid_argument("nazivnik ne smije biti nula!");
  else {
    numerator_ = numerator;
    denominator_ = denominator;
    skrati();
    predznak();
  }
}

Rational::Rational(const std::string& input) {
  std::string numerator, denominator;
  int znak{1};
  auto i = input.begin();
  if (input.front() == '-') {
    ++i;
    znak = -1;
  }
  for (; i != input.end(); ++i) {
    if (*i >= '0' && *i <= '9')
      numerator.push_back(*i);
    else if (*i == '/')
      break;
    else
      throw std::invalid_argument("pogresan unos");
  }
  numerator_ = stoi(numerator) * znak;

  if (i == input.end())
    denominator_ = 1;

  else if (*i == '/') {
    znak=1;
    ++i;
    if (*i == '-') {
      ++i;
      znak = -1;
    }
    for (; i != input.end(); ++i) {
      if (*i >= '0' && *i <= '9')
        denominator.push_back(*i);
      else
        throw std::invalid_argument("pogresan unos");
    }
    denominator_ = stoi(denominator) * znak;
    if(!denominator_)throw std::invalid_argument("nula u nazivniku");
    skrati();
    predznak();
  }
}


Rational::Rational(const char* rational){
  std::string input{rational};
std::string numerator, denominator;
  int znak{1};
  auto i = input.begin();
  if (input.front() == '-') {
    ++i;
    znak = -1;
  }
  for (; i != input.end(); ++i) {
    if (*i >= '0' && *i <= '9')
      numerator.push_back(*i);
    else if (*i == '/')
      break;
    else
      throw std::invalid_argument("pogresan unos");
  }
  numerator_ = stoi(numerator) * znak;

  if (i == input.end())
    denominator_ = 1;

  else if (*i == '/') {
    znak=1;
    ++i;
    if (*i == '-') {
      ++i;
      znak = -1;
    }
    for (; i != input.end(); ++i) {
      if (*i >= '0' && *i <= '9')
        denominator.push_back(*i);
      else
        throw std::invalid_argument("pogresan unos");
    }
    denominator_ = stoi(denominator) * znak;
    if(!denominator_) throw std::invalid_argument("nula u nazivniku");
    skrati();
    predznak();
  }

}


Rational::Rational(const Rational& rational)
    : numerator_{rational.numerator_}, denominator_{rational.denominator_} {}

Rational::Rational(Rational&& rational)
    : numerator_{rational.numerator_}, denominator_{rational.denominator_} {
  rational.numerator_ = 0;
  rational.denominator_ = 1;
}

Rational& Rational::operator=(const Rational& rational) {
  numerator_ = rational.numerator_;
  denominator_ = rational.denominator_;
  return *this;
}

Rational& Rational::operator=(Rational&& rational) {
  numerator_ = rational.numerator_;
  denominator_ = rational.denominator_;
  rational.numerator_ = 0;
  rational.denominator_ = 1;
  return *this;
}

Rational Rational::operator+(const Rational& rational) const {
  Rational result{};
  result.numerator_ =
      numerator_ * rational.denominator_ + denominator_ * rational.numerator_;
  result.denominator_ *= denominator_ * rational.denominator_;
  result.skrati();
  result.predznak();
  return result;
}

Rational Rational::operator+(int numerator) const {
  Rational result{*this};
  result.numerator_ += numerator * result.denominator_;
  result.skrati();

  result.predznak();

  return result;
}

Rational Rational::operator-(const Rational& rational) const {
  Rational result{};
  result.numerator_ =
      numerator_ * rational.denominator_ - denominator_ * rational.numerator_;
  result.denominator_ *= denominator_ * rational.denominator_;
  result.skrati();

  result.predznak();
  return result;
}
Rational Rational::operator-(int numerator) const {
  Rational result{*this};
  result.numerator_ -= numerator * result.denominator_;
  result.skrati();
  result.predznak();
  return result;
}

Rational Rational::operator*(const Rational& rational) const {
  Rational result{*this};
  result.numerator_ *= rational.numerator_;
  result.denominator_ *= rational.denominator_;
  result.skrati();
  result.predznak();
  return result;
}
Rational Rational::operator*(int numerator) const {
  Rational result{*this};
  result.numerator_ *= numerator;
  result.skrati();

  result.predznak();
  return result;
}

Rational Rational::operator/(const Rational& rational) const {
  Rational result{*this};
  result.numerator_ *= rational.denominator_;
  result.denominator_ *= rational.numerator_;
  result.skrati();

  result.predznak();
  return result;
}

Rational Rational::operator/(int numerator) const {
  Rational result{*this};
  if (numerator == 0)
    throw std::invalid_argument("nemoguce je dijeliti sa nulom");
  else {
    result.denominator_ *= numerator;
    result.skrati();

    result.predznak();
    return result;
  }
}

Rational Rational::operator^(int power) const {
  Rational result{*this};
  result.numerator_ = pow(numerator_, power);
  result.denominator_ = pow(denominator_, power);
  return result;
}

Rational& Rational::operator++() {
  numerator_ += denominator_;
  skrati();
  predznak();
  return *this;
}

Rational Rational::operator++(int) {
  Rational result{*this};
  ++(*this);
  return result;
}

Rational& Rational::operator--() {
  numerator_ -= denominator_;
  skrati();
  predznak();
  return *this;
}

Rational Rational::operator--(int) {
  Rational result{*this};
  --(*this);
  return result;
}

bool Rational::operator==(const Rational& rational) const {
  if (rational.numerator_ == numerator_ &&
      rational.denominator_ == denominator_)
    return true;
  else
    return false;
}
bool Rational::operator==(const char* rational) const {
  Rational input(rational);
  if (*this == input)
    return true;
  else
    return false;
}

bool Rational::operator!=(const Rational& rational) const {
  if (rational.numerator_ == numerator_ &&
      rational.denominator_ == denominator_)
    return true;
  else
    return false;
}

bool Rational::operator!=(const char* rational) const {
  Rational input(rational);
  if (*this != input)
    return true;
  else
    return false;
}

const int Rational::numerator() const { return numerator_; }
const int Rational::denominator() const { return denominator_; };

Rational::~Rational() {}

int normalize(const int numerator, const int denominator) {
  int this_gcd = gcd(numerator, denominator);
  if (this_gcd != 1 && denominator / this_gcd == 1)
    return numerator / this_gcd;
  else
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Rational& rational) {
  if (rational.denominator() == 1)
    os << rational.numerator() << std::endl;
  else {
    os << rational.numerator() << "/" << rational.denominator();
  }
  return os;
}

std::istream& operator>>(std::istream& is, Rational& rational){
  std::string s;
  std::getline(is,s);
  rational = Rational{s};
  return is;
}
