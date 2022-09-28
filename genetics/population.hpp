#pragma once
#include <tuple>
#include <cmath>
#include "agent.hpp"

class Population{
    public:
        Population(int size, Program* program, double mutationRate, double mutationRange);
        void update();
        std::map<std::string, double>  getBest();
    private:
        int size;
        Program* program;
        double mutationRate, mutationRange;
        std::map<std::string, Range> variables;
        std::tuple<double, double> objectiveRange;
        std::list<Agent*> agents;
        std::tuple<double, std::map<std::string, double>> best;
        std::list<Agent*> getChildren(double overallFitness);
        Agent* getChild(double overallFitness);
        std::tuple<double, double> getObjectiveRange();
};