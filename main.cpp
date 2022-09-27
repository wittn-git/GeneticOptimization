#include <iostream>
#include "parser/parser.hpp"
#include "util/file_util.hpp"

int main(){
    Parser parser;
    std::string data = read_file("input.txt");
    Program prog = parser.parse(data);
    std::cout << prog.to_string();
    return 0;
}