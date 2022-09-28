#include <iostream>
#include "parser/parser.hpp"
#include "util/file_util.hpp"
#include "genetics/population.hpp"

int main(){
    Parser parser;
    std::string input = read_file("input.txt");
    Program prog = parser.parse(input);
    std::cout << "Parsed program:\n" << prog.to_string();
    Population population(100, &prog, 0.05, 1);
    for(int i=0; i<100; i++){
        population.update();
        std::map<std::string, double> best = population.getBest();
        std::cout << prog.getObjective()->eval(best) << "\n";
        for(const auto& elem : best){
            std::cout << elem.first << " " << elem.second << "\n";
        }
        std::cout << "\n";
    }
    return 0;
}