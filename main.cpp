#include <iostream>
#include "parser/parser.hpp"

int main(){
    Parser parser;
    Program prog = parser.parse("objective: 3x; constraints: 2x=5x;5y<=3x;");
    std::cout << prog.to_string() << std::endl;//prog.to_string()
    return 0;
}