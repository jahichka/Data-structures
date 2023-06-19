#include <iostream>
#include <string>
#include "Library.cpp"

int main(void) {
  std::cout << "University of Tuzla\nFaculty of Electrical "
               "Engineering\n\nLibrary application\nVerson:April 2023.\n\n"
            << std::endl;
  std::cout << std::string(30, '=') << "\n" << std::endl;
  Library library{};
  library.Help();
  printDividers();
  std::cout << "Enter command: ";
  std::string command;
  while (std::cin >> command) {
    if (command == "CreateUser") {
      printDividers();
      std::string s1,s2;
      int n;
      std::cout << "First name: ";
      std::cin >> s1;
      std::cout << "Last name: ";
      std::cin >> s2;
      std::cout << "User ID: ";
      std::cin >> n; 
      library.addUser(s1,s2,n);
      printDividers();
    } else if (command == "BookAdd") {
      printDividers();
      std::string s1,s2,s3;
      unsigned short m;
      size_t n;
      std::cout << "Title: ";
      std::cin >> s1;
      std::cout << "Author: ";
      std::cin >> s2;
      std::cout << "Publisher: ";
      std::cin >> s3;
      std::cout << "Publication year: ";
      std::cin >> m;
      std::cout<<"Number of copies: ";
      std::cin>>n;
      library.newBook(s1,s2,s3,m,n);
      printDividers();
    } else if (command == "BookLend") {
      printDividers();
      std::string s;
      int n;
      std::cout << "User ID: ";
      std::cin >> n;
      std::cout << "Book Title: ";
      std::cin >> s;
      library.lendBook(n, s);
      printDividers();
    } else if (command == "BookReturn") {
      printDividers();
      std::string s;
      int n;
      std::cout << "User ID: ";
      std::cin >> n;
      std::cout << "Book Title: ";
      std::cin >> s;
      library.returnBook(n, s);
      printDividers();
    } else if (command == "BookSearchByTitle") {
      printDividers();
      std::string s;
      std::cout << "Book title:";
      std::cin >> s;
      library.findBookByTitle(s);
      printDividers();
    } else if (command == "BookSearchByAuthor") {
      printDividers();
      std::string s;
      std::cout << "Book author:";
      std::cin >> s;
      library.findBookByAuthor(s);
      printDividers();
    } else if (command == "BookSearchByPublisher") {
      printDividers();
      std::string s;
      std::cout << "Book year:";
      std::cin >> s;
      library.findBookByPublisher(s);
      printDividers();
    } else if (command == "BookSearchByPublicationYear") {
      printDividers();
      int s;
      std::cout << "Book year:";
      std::cin >> s;
      library.findBookByPublicationYear(s);
      printDividers();
    } else if (command == "Help") {
      library.Help();
    } else if (command == "Exit") {
      std::cout << "Goodbye!" << std::endl;
      printDividers();
      return 0;
    } else {
      printDividers();
      std::cout << "Invalid command." << std::endl;
      printDividers();
    }
    printDividers();
    std::cout<<"Enter command: "<<std::endl;
  }
}

