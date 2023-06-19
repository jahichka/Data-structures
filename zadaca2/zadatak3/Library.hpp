#pragma once
#include <vector>
#include "Book.hpp"
#include "User.hpp"


namespace Payments{
  short childrenMembership{10};
  short studentMembership{15};
  short adultMembership{20};
  short elderMembership{10};
  short feeOneMonth{1};
  short feeFourMonths{5};
  short feedSixMonths{10};
}


class Library{
private:
  std::vector<Book> books{};
  std::vector<User> users{};
  std::vector<User>::iterator findUser(int);
  std::vector<Book>::iterator findBook(const std::string&);
  
public:
  void newBook(const std::string&);
  void returnBook(size_t,const std::string&);
  void lendBook(size_t, const std::string&);
  void findBookByTitle(const std::string&)const;
  void findBookByAuthor(const std::string&)const;
  void findBookByPublisher(const std::string&)const;
  void findBookByPublicationYear(const unsigned short)const;
  void deleteBook(const std::string&);
  void addUser(const std::string&);
  void deleteUser(size_t);
  void membershipUser(const std::string&);
  void Help();
};


