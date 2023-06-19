#include <iostream>
#include <sstream>
#include <stack>
#include <string>

int main() {
    char c;
    std::string str;
    std::stringstream ss;
    while (getline(std::cin, str)) {
        std::stack<char> braces;
        bool error = false; 

        for (auto& c : str) {
            switch (c) {
                case '{':
                case '[':
                case '(':
                case '<':
                    braces.push(c);
                    break;

                case '}':
                    if (braces.empty() || braces.top() != '{')
                        error = true;
                    else
                        braces.pop();
                    break;

                case ']':
                    if (braces.empty() || braces.top() != '[')
                        error = true;
                    else
                        braces.pop();
                    break;

                case ')':
                    if (braces.empty() || braces.top() != '(')
                        error = true;
                    else
                        braces.pop();
                    break;

                case '>':
                    if (braces.empty() || braces.top() != '<')
                        error = true;
                    else
                        braces.pop();
                    break;

                default:
                error=true;
                    break;
            }

            if (error)
                break;  
        }

        if (error || !braces.empty())
            std::cout << "pogresan" << std::endl;
        else
            std::cout << "dobar" << std::endl;
    }
}
