#include <iostream>
#include "parser/parser.hpp"
#include "util/file_util.hpp"
#include "genetics/population.hpp"

#define epoches 300
#define populationsize 100
#define mutationrate 0.05
#define mutationrange 0.2

int main(){
    Parser parser;
    std::string input = read_file("input.txt");
    Program prog = parser.parse(input);
    std::cout << "Parsed program:\n" << prog.to_string();
    Population population(populationsize, &prog, mutationrate, mutationrange);
    for(int i=0; i<epoches; i++){
        population.update();
        std::cout << population.to_string() << "\n";
    }
    return 0;
}