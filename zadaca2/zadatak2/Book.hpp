#pragma once
#include <iostream>
#include <sstream>
#include <string>

class Book {
  private:
  std::string title_{};
  std::string author_{};
  std::string publisher_{};
  unsigned short year_{0};
  size_t num_of_copies_{0};

  public:
  Book();
  Book(const std::string&,const std::string&,const std::string&,unsigned short,size_t);
  bool operator==(const Book&) const;
  operator bool const()const ;
  bool currentCopies() const;
  void retrn();
  void lend();
  const std::string& titleGetter() const;
  const std::string& authorGetter() const;
  const std::string& publisherGetter() const;
  const unsigned short yearGetter() const;
  size_t copiesGetter() const;
  operator bool() const;
};

std::ostream& operator<<(std::ostream& out, const Book&);

