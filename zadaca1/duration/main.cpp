#include <iostream>
#include "duration.hpp"
#include "duration.cpp"
int main() {
  // ovdje možete samostalno testirati neke funkcionalnosti. 
  // Napomena: main.cpp se ne pregleda, sva implementacija 
  // ide u duration .cpp i .hpp fileove.
  
  Duration d1{1, 2, 3};
  std::cout << (d1 + Duration{3, 2, 1}) << std::endl;
  std::cout<<!d1<<std::endl;
}
