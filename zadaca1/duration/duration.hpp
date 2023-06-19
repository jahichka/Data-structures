#pragma once
#include <iostream>
#include <string>

class Duration {
  private:
  int hour_{0};
  int minute_{0};
  int second_{0};

  public:
  Duration();
  Duration(const Duration& d);
  Duration(Duration&& d);
  Duration& operator=(const Duration& d);
  Duration& operator=(Duration&& d);
  ~Duration();

  Duration(int seconds);
  Duration(int hours, int minutes, int seconds);
  Duration(const std::string& s);

  Duration& set_s(int seconds);
  Duration& set_m(int minutes);
  Duration& set_h(int hours);
  int get_s();
  int get_m();
  int get_h();

  operator bool() const;
  bool operator!() const;
  bool operator==(const Duration& d) const;
  bool operator!=(const Duration& d) const;
  int transform_to_seconds() const;

  bool operator>(const Duration& d) const;
  bool operator<(const Duration& d) const;
  bool operator>=(const Duration& d) const;
  bool operator<=(const Duration& d) const;

  Duration& operator+=(const Duration& d);
  Duration operator+(const Duration& d) const;
  Duration& operator-=(const Duration& d);
  Duration operator-(const Duration& d) const;
  Duration& operator*=(const int constant);
  Duration operator*(const int constant) const;
  Duration& operator/=(const int constant);
  Duration operator/(const int constant) const;

  friend std::ostream& operator <<(std::ostream& out, const Duration& d);
  friend std::istream& operator >>(std::istream& in, Duration& d);
};
