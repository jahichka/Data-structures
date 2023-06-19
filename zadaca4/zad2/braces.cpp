#include <stack>
#include <iostream>
#include <string>
#include <sstream>

class Bolt{
    private:
    std::stack<char> braces;
    public:
    void input(std::istream& in){
        std::stringstream ss;
        std::string s;
        in>>s;
        ss<<s;
        
    }
};