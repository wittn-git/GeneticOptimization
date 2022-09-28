#include "population.hpp"

Population::Population(int size, Program* program, double mutationRate, double mutationRange) : size(size), program(program), mutationRate(mutationRate), mutationRange(mutationRange) {
    variables = program->getVariables();
    for(int i=0; i<size; i++){
        agents.emplace_back(new Agent(variables));
    }
    objectiveRange = getObjectiveRange();
};

void Population::update(){
    double overallFitness = 0;
    for(auto it = agents.begin(); it != agents.end(); ++it){
        double fitness = (*it)->calculateFitness(program, objectiveRange);
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

std::tuple<double, double> Population::getObjectiveRange(){
    std::map<std::string, double> mins, maxs;
    for(auto it = variables.begin(); it != variables.end(); it++){
        mins[(*it).first] = (*it).second.min;
        maxs[(*it).first] = (*it).second.max;    
    }
    double min = program->getObjective()->eval(mins);
    double max = program->getObjective()->eval(maxs);
    return { min, std::fabs((max - min)) };
}