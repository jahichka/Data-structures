#include "Library.hpp"
#include <iostream>
#include <vector>
#include "User.cpp"

void printDividers() {
  std::cout << std::endl;
  std::cout << std::string(30, '=') << std::endl;
  std::cout << std::endl;
}

std::vector<User>::iterator Library::findUser(int ID) {
  for (auto& i : users)
    if (i.IDGetter() == ID) {
      return std::vector<User>::iterator{&i};
    }
  return users.end();
}

std::vector<Book>::iterator Library::findBook(const std::string& in) {
  for (auto& i : books) {
    if (i.titleGetter() == in) {
      return std::vector<Book>::iterator{&i};
    }
  }
return books.end();
}

void Library::newBook(const std::string& in) {
  if (findBook(in)!=books.end()) {
    std::cout << "Book already exists" << std::endl;
  } else {
    books.push_back(Book{in});
    std::cout << "Book sucessfully added" << std::endl;
    return;
  }
}

void Library::returnBook(size_t ID, const std::string& in) {
  std::vector<User>::iterator user{findUser(ID)};

  if (user!=users.end()) {
    std::vector<Book>::iterator book;
    book = (*user).borrowedBookGetter();
    if (book!=books.end()) {
      if (*book == Book{in}) {
        (*book).retrn();
        book = books.end();
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
  std::vector<User>::iterator user{findUser(ID)};
  if (user!=users.end()) {
    std::vector<Book>::iterator book;
    book = (*user).borrowedBookGetter();
    if (book!=books.end()) {
      std::cout << "Book already lent." << std::endl;
    } else {
      book = findBook(std::move(in));
      if(book!=books.end()){
      if (book->currentCopies() != 0) {
        (*book).lend();
        (*user).borrowedBookGetter() = book;
        std::cout << "Book sucessfully lent." << std::endl;
      } else
        std::cout << "No copies available" << std::endl;
      }else {
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
  std::vector<Book>::iterator book{ findBook(in)};
  if(book!=books.end()) {
    std::cout << "Book not found" << std::endl;
    return;
  }
  books.erase(book);
}

void Library::addUser(const std::string& in) {
  User user{in};
    if(findUser(user.IDGetter())!=users.end()){
    std::cout << "User already exists" << std::endl;
  } else {
    users.push_back(user);
    std::cout << "User added successfully" << std::endl;
  }
}

void Library::deleteUser(size_t ID) {
  std::vector<User>::iterator user{findUser(ID)};
  if(user!=users.end())
  {
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
