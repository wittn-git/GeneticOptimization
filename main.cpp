#include <iostream>
#include "parser/parser.hpp"

int main(){
    Parser parser;
    Program prog = *(parser.parse("objective: 3x; constraints: 2x=5x;"));
    std::cout << "2" << std::endl;//prog.to_string()
}