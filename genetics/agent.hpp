#pragma once
#include <set>
#include <string>
#include "../util/random_util.hpp"
#include "../structure/program.hpp"

class Agent{
    public:
        Agent(std::map<std::string, Range> variables);
        Agent(std::map<std::string, double> values);
        Agent(Agent* agent, double mutationRate, double mutationRange);
        std::map<std::string, double> getValues();
        double calculateFitness(Program* program, std::tuple<double, double> objectiveRange, std::list<std::tuple<double, double>> constraintRanges);
        double getFitness();
    private:
        std::map<std::string, double> values;
        double fitness;
        double getMutationValue(double mutationRange);
};