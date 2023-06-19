#pragma once
#include <iostream>
#include <string>
#include "Book.hpp"
#include "../zadatak1/MojVektor.hpp"
/*struct date {
  private:
  short day_{1};
  short month_{1};
  short year_{1900};

  public:
  date();
  date(short, short, short);
  date(std::string);
  date& operator=(const date&);
  const date& getDate() const;
  void setDate(std::string);
  const short getMonth() const;
  const short getDay() const;
  const short getYear() const;
  unsigned short period(const date& d) const;
};

std::istream& operator << (std::istream& in, date& d);*/

class User {
  private:
  std::string name_{};
  std::string last_name_{};
  int ID_{0};
  //std::string status_{};
  MojVektor<Book>::Iterator borrowedBook_;
  // date lendDate_{};
  // date membershipDate_{};

  public:
  User();
  User(const std::string&);
  User(const std::string&,const std::string&,int);
  const std::string& nameGetter() const;
  const std::string& lastNameGetter() const;
  int IDGetter() const;
  const std::string& statusGetter() const;
  void statusSetter(std::string&);
  MojVektor<Book>::Iterator& borrowedBookGetter();
  void borrowedBookSetter(MojVektor<Book>::Iterator);
  // date lendDateGetter() const;
  // void lendDateSetter(std::string&);
  // date membershipDateGetter() const;
  // void membershipDateSetter(std::string&);
};
