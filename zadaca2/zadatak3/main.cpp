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
      std::stringstream ss;
      std::string s;
      std::cout << "First name: ";
      std::cin >> s;
      ss << s<<" ";
      std::cout << "Last name: ";
      std::cin >> s;
      ss << s<<" ";
      std::cout << "User ID: ";
      std::cin >> s;
      ss << s<< " ";
      ss >> s;
      library.addUser(s);
      printDividers();
    } else if (command == "BookAdd") {
      printDividers();
      std::stringstream ss;
      std::string s;
      std::cout << "Title: ";
      std::cin >> s;
      ss << s<<" ";
      std::cout << "Author: ";
      std::cin >> s;
      ss << s<<" ";
      std::cout << "Publisher: ";
      std::cin >> s;
      ss << s<<" ";
      std::cout << "Publication year: ";
      std::cin >> s;
      std::cout<<"Number of copies: ";
      std::cin>>s;
      ss << s<<" "; 
      ss >> s;
      library.newBook(s);
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

