#include <iostream>
#include <sstream>
#include <string>
#include "User.hpp"
#include "Book.cpp"
#include "Book.hpp"
/*bool correctDate(date d) {
  switch (d.getMonth()) {
    case 1:
      return (d.getDay() >= 1) && (d.getDay() <= 31);
    case 2:
      return (d.getDay() >= 1) && (d.getDay() <= 29) && (d.getYear() % 4 == 0);
    case 3:
      return (d.getDay() >= 1) && (d.getDay() <= 31);
    case 4:
      return (d.getDay() >= 1) && (d.getDay() <= 30);
    case 5:
      return (d.getDay() >= 1) && (d.getDay() <= 31);
    case 6:
      return (d.getDay() >= 1) && (d.getDay() <= 30);
    case 7:
      return (d.getDay() >= 1) && (d.getDay() <= 31);
    case 8:
      return (d.getDay() >= 1) && (d.getDay() <= 31);
    case 9:
      return (d.getDay() >= 1) && (d.getDay() <= 30);
    case 10:
      return (d.getDay() >= 1) && (d.getDay() <= 31);
    case 11:
      return (d.getDay() >= 1) && (d.getDay() <= 30);
    case 12:
      return (d.getDay() >= 1) && (d.getDay() <= 31);
    default:
      return false;
  }
}

date::date() {}
date::date(short day, short month, short year)
    : day_{day}, month_{month}, year_{year} {}
date::date(std::string in) {
  std::stringstream ss{std::move(in)};
  ss >> day_ >> month_ >> year_;
}
std::ostream& operator<<(std::ostream& out, date& d) {
  std::string delimiter{"."};
  out << d.getDay() << delimiter << d.getMonth() << delimiter << d.getYear()
      << delimiter;
  return out;
}

const date& date::getDate() const { return *this; }

void date::setDate(std::string in) { *this = date{in}; }

const short date::getDay() const { return day_; }

const short date::getMonth() const { return month_; }

const short date::getYear() const { return year_; }

unsigned short date::period(const date& d) const {
  if (year_ == d.year_) {
    if (day_ < d.day_)
      return d.month_ - month_;
    else
      return d.month_ - month_ - 1;
  } else if (year_ < d.year_) {
    unsigned short difference = d.year_ - year_;
    if (day_ < d.day_)
      return 12 - month_ + d.month_ + (difference == 1 ? 0 : difference * 12);
    else
      return 12 - month_ + d.month_ - 1 +
             (difference == 1 ? 0 : difference * 12);
  }
  else throw std::logic_error("");
}*/

User::User() {}
User::User(const std::string& in) {
  std::stringstream ss{in};
  ss >> name_ >> last_name_ >> ID_ >> status_;
}
const std::string& User::nameGetter() const { return name_; }
const std::string& User::lastNameGetter() const { return last_name_; }
int User::IDGetter() const { return ID_; }
const std::string& User::statusGetter() const { return status_; }
void User::statusSetter(std::string& s) { status_ = s; }
std::vector<Book>::iterator& User::borrowedBookGetter() { return borrowedBook_; }
void User::borrowedBookSetter(std::vector<Book>::iterator book) { borrowedBook_ = book;} 
// date User::lendDateGetter() const { return lendDate_; }
// void User::lendDateSetter(std::string& in) { lendDate_.setDate(in); }
// date User::membershipDateGetter() const { return membershipDate_; }
// void User::membershipDateSetter(std::string& in) {
//   membershipDate_.setDate(in);
// }


