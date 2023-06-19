#include <fstream>
#include <string>
#include "Rational.cpp"
#include "Rational.hpp"

int main(void) {
  std::ifstream in{"input.txt"};
  if (!in) {
    std::cout << "desila se greska" << std::endl;
  }

  std::string s;
  Rational r{};
  try {
    while (in >> r) {
      std::cout << r << std::endl;
    }
  } catch (std::exception& ex) {
    std::cout << ex.what() << std::endl;
  }
  in.close();

  // konstruktori
  Rational r1{};
  Rational r2{-2, 48};
  try {
    Rational r3{2, 0};
  } catch (std::exception& ex) {
  }
  r1 = r2;
  Rational r4{std::move(r2)};
  Rational r5{"16/-256"};
  std::string rational = "225/25";
  Rational r6{rational};
  r1 = Rational{-2, 5};

  // aritmetricki operatori
  std::cout << Rational{-7, 6} + Rational{1, 3} << std::endl;
  std::cout << Rational{5, -2} + 2 << std::endl;
  std::cout << Rational{7, 6} - Rational{1, 3} << std::endl;
  std::cout << Rational{5, 2} - 2 << std::endl;
  std::cout<<Rational{1,2}*Rational{4,7}<<std::endl;
  std::cout<<Rational{7,16}*2<<std::endl;
  std::cout<<Rational{7,9}/Rational{1,3}<<std::endl;
  std::cout<<Rational{16,25}/2<<std::endl;
  std::cout<<(Rational{2,-3}^3)<<std::endl;

  r1 = Rational{1, 3};
  r2 = Rational{1, 2};
  r4 = Rational{7, 6};
  r5 = Rational{5, 4};
  // inkrementi i dekrementi
  std::cout << r1++ << " " << r1 << std::endl;
  std::cout << r2 << " " << (++r2) << std::endl;
  std::cout << r4-- << " " << r1 << std::endl;
  std::cout << r5 << " " << (--r5) << std::endl;

  // logicki operatori
  std::cout << (Rational{2, 1} == Rational{4, 2}) << std::endl;
  std::cout << (Rational{7, 8} == "7/8") << std::endl;
  std::cout << (Rational{2, 3} != Rational{4, 2}) << std::endl;
  std::cout << (Rational{7, 15} != "6/8") << std::endl;
}
