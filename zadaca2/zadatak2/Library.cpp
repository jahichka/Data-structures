#include "Library.hpp"
#include <iostream>
#include "../zadatak1/MojVektor.hpp"
#include "User.cpp"

void printDividers() {
  std::cout << std::endl;
  std::cout << std::string(30, '=') << std::endl;
  std::cout << std::endl;
}

User* Library::findUser(int ID) {
  for (auto& i : users)
    if (i.IDGetter() == ID) {
      return &i;
    }
  return nullptr;
}

bool Library::existUser(User* p){
  return p;
}

bool Library::existBook(Book* p){
return p;}

Book* Library::findBook(const std::string& in) {
  for (auto& i : books) {
    if (i.titleGetter() == in) {
      return &i;
    }
  }
  return nullptr;
}

void Library::newBook(const std::string& s1, const std::string& s2,
                      const std::string& s3, unsigned short m, size_t n) {
  if (existBook(findBook(s1))) {
    std::cout << "Book already exists" << std::endl;
  } else {
    books.push_back(Book{s1,s2,s3,m,n});
    std::cout << "Book sucessfully added" << std::endl;
    return;
  }
}

void Library::returnBook(size_t ID, const std::string& in) {
  MojVektor<User>::Iterator user{findUser(ID)};
  if (existUser(findUser(user))) {
    MojVektor<Book>::Iterator book;
    book = (*user).borrowedBookGetter();
    if (book) {
      if (book->titleGetter() == in) {
        (*book).retrn();
        book = nullptr;
        std::cout << "Book sucessfully returned" << std::endl;
      } else
        std::cout << "No book under with that title have been lent."
                  << std::endl;
    } else
      std::cout << "No books have been lent" << std::endl;
  } else {
    std::cout << "User not found" << std::endl;
  }
}

void Library::lendBook(size_t ID, const std::string& in) {
  MojVektor<User>::Iterator user{findUser(ID)};
  if (existUser(findUser(user))) {
    MojVektor<Book>::Iterator book;
    book = (*user).borrowedBookGetter();
    if (book) {
      std::cout << "Book already lent." << std::endl;
    } else {
      book = findBook(std::move(in));
      if (book) {
        if (book->currentCopies() != 0) {
          (*book).lend();
          (*user).borrowedBookGetter() = book;
          std::cout << "Book sucessfully lent." << std::endl;
        } else
          std::cout << "No copies available" << std::endl;
      } else {
        std::cout << "Book not found" << std::endl;
      }
    }
  } else {
    std::cout << "User not found" << std::endl;
  }
}

void Library::findBookByAuthor(const std::string& author) const {
  for (auto& i : books) {
    if (i.authorGetter() == author) {
      std::cout << i;
      printDividers();
    }
  }
}

void Library::findBookByTitle(const std::string& title) const {
  for (auto& i : books) {
    if (i.titleGetter() == title) {
      std::cout << i;
      printDividers();
    }
  }
}

void Library::findBookByPublisher(const std::string& publisher) const {
  for (auto& i : books) {
    if (i.publisherGetter() == publisher) {
      std::cout << i;
      printDividers();
    }
  }
}

void Library::findBookByPublicationYear(const unsigned short year) const {
  for (auto& i : books) {
    if (i.yearGetter() == year) {
      std::cout << i;
      printDividers();
    }
  }
}

void Library::deleteBook(const std::string& in) {
  MojVektor<Book>::Iterator book{findBook(in)};
  if (!book) {
    std::cout << "Book not found" << std::endl;
    return;
  }
  books.erase(book);
}

void Library::addUser(const std::string& s1,const std::string& s2,int n) {
  User user{s1,s2,n};
  if (findUser(user.IDGetter())) {
    std::cout << "User already exists" << std::endl;
  } else {
    users.push_back(user);
    std::cout << "User added successfully" << std::endl;
  }
}

void Library::deleteUser(size_t ID) {
  MojVektor<User>::Iterator user{findUser(ID)};
  if (!user) {
    std::cout << "User not found" << std::endl;
    return;
  }
  users.erase(user);
}

void Library::Help() {
  std::cout << "List of commands" << std::endl;
  std::cout << std::string(30, '=') << std::endl;
  std::cout << "CreateUser" << std::endl;
  std::cout << "BookAdd" << std::endl;
  std::cout << "BookLend" << std::endl;
  std::cout << "BookReturn" << std::endl;
  std::cout << "BookSearchByTitle" << std::endl;
  std::cout << "BookSearchByAuthor" << std::endl;
  std::cout << "BookSearchByPublisher" << std::endl;
  std::cout << "BookSearchByPublicationYear" << std::endl;
  std::cout << "UserMembership" << std::endl;
  std::cout << "Help" << std::endl;
  std::cout << "Exit" << std::endl;
}

void Library::membershipUser(const std::string&) {}
