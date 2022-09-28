#include "population.hpp"

Population::Population(int size, Program* program, double mutationRate, double mutationRange) : size(size), program(program), mutationRate(mutationRate), mutationRange(mutationRange) {
    std::map<std::string, Range> variableNames = program->getVariables();
    for(int i=0; i<size; i++){
        agents.emplace_back(new Agent(variableNames));
    }
};

void Population::update(){
    double overallFitness = 0;
    for(auto it = agents.begin(); it != agents.end(); ++it){
        double fitness = (*it)->calculateFitness(program);
        if(fitness > std::get<0>(best)){
            best = {fitness, (*it)->getValues() };
        }
        overallFitness += fitness;
    }
    agents = getChildren(overallFitness);
}

std::map<std::string, double> Population::getBest(){
    return std::get<1>(best);
}

std::list<Agent*> Population::getChildren(double overallFitness){
    std::list<Agent*> newAgents = { new Agent(std::get<1>(best)) };
    while(newAgents.size() < size){
        newAgents.emplace_back(getChild(overallFitness));
    }
    return newAgents;
}

Agent* Population::getChild(double overallFitness){
    double runningSum = 0;
    double target = getRandom(0, overallFitness);
    for(auto it = agents.begin(); it != agents.end(); ++it){
        runningSum += (*it)->getFitness();
        if(runningSum >= target){
            return new Agent(*it, mutationRate, mutationRange);
        }
    }
    return nullptr;
}