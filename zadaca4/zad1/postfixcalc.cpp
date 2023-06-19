#include <cctype>
#include <iostream>
#include <sstream>
#include <sstring>
#include <stack>
#include <stdexcept>
#include <string>

class PostfixCalc {
private:
  std::stack<int> calc;

public:
  int calculate(std::string str) {
    std::string token;
    std::stringstream ss(str);
    while (ss >> token) {
      if (token.size()==1){
        int num1, num2;
        num1 = calc.top();
        calc.pop();
        num2 = calc.top();
        calc.pop();
        switch (token[0]) {
        case '+':
          calc.push(num1 + num2);
          break;
        case '-':
          calc.push(num1 - num2);
          break;
        case '*':
          calc.push(num1 * num2);
          break;
        case '/':
          if (num2 != 0)
            calc.push(num1 + num2);
          else
            throw std::out_of_range("");
          break;
          default:
          if(token[0]>'9'&&token[0]<'0') throw std::out_of_range("");
          break;
        }
        break;
      }
      else {
        char c=token.front();
        if(c!='-'&&(c<'0'||c>'9')) throw std::out_of_range("");
        else{
            if (c!='-'){
                for()
            }
        }
      }

    }
  }
};