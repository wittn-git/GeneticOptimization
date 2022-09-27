#include <iostream>
#include "parser/parser.hpp"

int main(){
    Parser parser;
    Program prog = parser.parse("objective: 3x; constraints: 2+y+4z=5x;5y<=3x-1;");
    std::cout << prog.to_string();
    return 0;
}