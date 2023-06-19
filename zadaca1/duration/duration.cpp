#include "duration.hpp"
#include <iostream>
#include <string>

Duration::Duration() {}
Duration::Duration(const Duration& d)
    : second_{d.second_}, minute_{d.minute_}, hour_{d.hour_} {}
Duration::Duration(Duration&& d)
    : second_{d.second_}, minute_{d.minute_}, hour_{d.hour_} {}

Duration& Duration::operator=(const Duration& d) {
  second_ = d.second_;
  minute_ = d.minute_;
  hour_ = d.hour_;
  return *this;
}

Duration& Duration::operator=(Duration&& d) {
  second_ = d.second_;
  minute_ = d.minute_;
  hour_ = d.hour_;
  return *this;
}

Duration::~Duration() {}

Duration::Duration(int seconds)
    : hour_{seconds / 3600},
      minute_{(seconds - hour_ * 3600) / 60},
      second_{seconds - hour_ * 3600 - minute_ * 60} {}
Duration& Duration::set_s(int seconds) {
  if (seconds < 60)
    second_ = seconds;
  else
    throw std::out_of_range("Broj sekundi mora biti manji od 60");
  return *this;
}

Duration& Duration::set_m(int minutes) {
  if (minutes < 60)
    minute_ = minutes;
  else
    throw std::out_of_range("Broj minuta mora biti manji od 60");
  return *this;
}

Duration& Duration::set_h(int hours) {
  hour_ = hours;
  return *this;
}

int Duration::get_s() { return second_; }

int Duration::get_m() { return minute_; }

int Duration::get_h() { return hour_; }

Duration::Duration(int hours, int minutes, int seconds) {
  set_h(hours);
  set_m(minutes);
  set_s(seconds);
}

Duration::operator bool() const {
  if (hour_ == 0 && minute_ == 0 && second_ == 0)
    return false;
  else
    return true;
}

bool Duration::operator!() const {
  if (*this)
    return false;
  else
    return true;
}

bool Duration::operator==(const Duration& d) const {
  if (hour_ == d.hour_ && minute_ == d.minute_ && hour_ == d.hour_)
    return true;
  else
    return false;
}

bool Duration::operator!=(const Duration& d) const {
  if (*this == d)
    return false;
  else
    return true;
}

int Duration::transform_to_seconds() const {
  return hour_ * 3600 + minute_ * 60 + second_;
}

bool Duration::operator>(const Duration& d) const {
  if (transform_to_seconds() > d.transform_to_seconds())
    return true;
  else
    return false;
}

bool Duration::operator<(const Duration& d) const {
  if (transform_to_seconds() < d.transform_to_seconds())
    return true;
  else
    return false;
}

bool Duration::operator>=(const Duration& d) const {
  if (transform_to_seconds() >= d.transform_to_seconds())
    return true;
  else
    return false;
}

bool Duration::operator<=(const Duration& d) const {
  if (transform_to_seconds() <= d.transform_to_seconds())
    return true;
  else
    return false;
}

Duration& Duration::operator+=(const Duration& d) {
  if (d) {
    int d_in_seconds = d.transform_to_seconds();
    int this_in_seconds = transform_to_seconds();
    *this = Duration(d_in_seconds + this_in_seconds);
  }
  return *this;
}

Duration Duration::operator+(const Duration& d) const {
  Duration result = *this;
  if (d) result += d;
  return result;
}

Duration& Duration::operator-=(const Duration& d) {
  if (*this < d)
    throw std::out_of_range("Nemoguce dobiti negativno vrijeme");
  else {
    if (d) {
      int d_in_seconds = d.transform_to_seconds();
      int this_in_seconds = transform_to_seconds();
      *this = Duration(d_in_seconds - this_in_seconds);
    }
    return *this;
  }
}

Duration Duration::operator-(const Duration& d) const {
  if (*this < d)
    throw std::out_of_range("Nemoguce dobiti negativno vrijeme");
  else {
    Duration result = *this;
    if (d) result -= d;
    return result;
  }
}

Duration& Duration::operator*=(const int constant) {
  int this_in_seconds = transform_to_seconds();
  this_in_seconds *= constant;
  *this = Duration(this_in_seconds);
  return *this;
}

Duration Duration::operator*(const int constant) const {
  int this_in_seconds = transform_to_seconds();
  this_in_seconds *= constant;
  Duration result(this_in_seconds);
  return result;
}

Duration& Duration::operator/=(const int constant) {
  int this_in_seconds = transform_to_seconds();
  this_in_seconds /= constant;
  *this = Duration(this_in_seconds);
  return *this;
}

Duration Duration::operator/(const int constant) const {
  int this_in_seconds = transform_to_seconds();
  this_in_seconds /= constant;
  Duration result(this_in_seconds);
  return result;
}

std::ostream& operator<<(std::ostream& out, const Duration& d) {
  char s = ':';
  out << d.hour_ << s << d.minute_ << s << d.second_ << std::endl;
  return out;
}

std::istream& operator>>(std::istream& in, Duration& d) {
  char s1, s2;
  int hour, minute, second;
  if ((in >> hour >> s1 >> minute >> s2 >> second) && s1 == ':' && s2 == ':') {
    d.set_s(second).set_m(minute).set_h(hour);
    return in;
  } else
    throw std::invalid_argument("Netacan unos");
}

Duration::Duration(const std::string& i) {
  std::string input;
  int input_as_int;
  for(auto j:i)
    if(j!=':')
      input.push_back(j);

  input_as_int=stoi(input);

  second_=input_as_int%10;
  input_as_int/=10;
  minute_=input_as_int%10;
  input_as_int/=10;
  hour_=input_as_int;
}

