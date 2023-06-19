#include "Book.hpp"

Book::Book() {}
Book::Book(const std::string& in) {
  std::stringstream ss{in};
  ss >> title_ >> author_ >> publisher_ >> year_ >> num_of_copies_;
}

bool Book::operator==(const Book& b) const {
  return ((title_ == b.title_) && (author_ == b.author_) &&
          (publisher_ == b.publisher_) && (year_ == b.year_));
}

Book::operator bool ()const {
  std::string emptystring;
  if ((title_ == emptystring) && (author_ == emptystring) &&
      (publisher_ == emptystring) && (year_ == 0))
    return false;
  else
    return true;
}

bool Book::currentCopies() const { return num_of_copies_; }

void Book::retrn() { ++num_of_copies_; }
void Book::lend() {
  if (currentCopies()) --num_of_copies_;
}

const std::string& Book::titleGetter() const { return title_; }

const std::string& Book::authorGetter() const { return author_; }

const std::string& Book::publisherGetter() const { return publisher_; }

const unsigned short Book::yearGetter() const { return year_; }

size_t Book::copiesGetter() const { return num_of_copies_; }

std::ostream& operator<<(std::ostream& out, const Book& i) {
  out << "Title: " << i.titleGetter() << std::endl;
  out << "Author: " << i.authorGetter() << std::endl;
  out << "Publisher: " << i.publisherGetter() << std::endl;
  out << "Year: " << i.yearGetter() << std::endl;
  out << std::string(30, '=');
  return out;
}
