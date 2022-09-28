#include <iostream>
#include "parser/parser.hpp"
#include "util/file_util.hpp"
#include "genetics/population.hpp"

#define epoches 100
#define populationsize 100
#define mutationrate 0.05
#define mutationrange 1

int main(){
    Parser parser;
    std::string input = read_file("input.txt");
    Program prog = parser.parse(input);
    std::cout << "Parsed program:\n" << prog.to_string();
    Population population(populationsize, &prog, mutationrate, mutationrange);
    for(int i=0; i<epoches; i++){
        population.update();
        std::map<std::string, double> best = population.getBest();
        std::cout << "Objective value: " << prog.getObjective()->eval(best) << "\n" << "Variables values:\n";
        for(const auto& elem : best){
            std::cout << elem.first << " " << elem.second << "\n";
        }
        std::cout << "\n";
    }
    return 0;
}