#pragma once
#include <set>
#include <string>
#include "../util/random_util.hpp"
#include "../structure/program.hpp"

class Agent{
    public:
        Agent(std::set<std::string> variableNames);
        Agent(std::map<std::string, double> values);
        Agent(Agent* agent, double mutationRate, double mutationRange);
        std::map<std::string, double> getValues();
        double calculateFitness(Program* program);
        double getFitness();
    private:
        std::map<std::string, double> values;
        double fitness;
        double getMutationValue(double mutationRange);
};