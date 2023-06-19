#pragma once
#include "../zadatak1/MojVektor.hpp"
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
  MojVektor<Book> books{};
  MojVektor<User> users{};
  User* findUser(int);
  Book* findBook(const std::string&);
  bool existUser(User*);
  bool existBook(Book*);
  
public:
  void newBook(const std::string&,const std::string&,const std::string&,unsigned short,size_t);
  void returnBook(size_t,const std::string&);
  void lendBook(size_t, const std::string&);
  void findBookByTitle(const std::string&)const;
  void findBookByAuthor(const std::string&)const;
  void findBookByPublisher(const std::string&)const;
  void findBookByPublicationYear(const unsigned short)const;
  void deleteBook(const std::string&);
  void addUser(const std::string&,const std::string&,int);
  void deleteUser(size_t);
  void membershipUser(const std::string&);
  void Help();
};


