#include "agent.hpp"
#include <iostream>

Agent::Agent(std::map<std::string, Range> variables){
    for(auto it = variables.begin(); it != variables.end(); ++it){
        values[(*it).first] = (*it).second.min;
    }
}

Agent::Agent(std::map<std::string, double> values) : values(values) {};

Agent::Agent(Agent* agent, double mutationRate, double mutationRange){
    std::map<std::string, double> parentValues = agent->getValues();
    for(auto it = parentValues.begin(); it != parentValues.end(); ++it){
        double value = (*it).second;
        if(getRandom(0,1) < mutationRate){
            value += getMutationValue(mutationRange);
        }
        values[(*it).first] = value;
    }
}

std::map<std::string, double> Agent::getValues(){
    return values;
}

double Agent::calculateFitness(Program* program, std::tuple<double, double> objectiveRange, std::list<std::tuple<double, double>> constraintRanges){
    double fitness = 0.1;
    double obj = program->getObjective()->eval(values) + std::get<0>(objectiveRange);
    fitness += (obj * 10) / std::get<1>(objectiveRange);
    std::list<EquationNode*> constraints = program->getConstraints();
    auto it1 = constraints.begin();
    auto it2 = constraintRanges.begin();
    for(; it1 != constraints.end() && it2 != constraintRanges.end(); ++it1, ++it2){
        std::tuple<bool, double> cstr = (*it1)->eval(values);
        if(!std::get<0>(cstr)){
            if((*it1)->getComparator() == E){
                fitness -= 5 * ((std::get<1>(cstr)) / std::get<1>(*it2));
            }else{
                fitness -= 5 * ((std::get<1>(cstr)) / std::get<1>(*it2));
                fitness -= 10 / constraints.size();
            }
        }
    }
    if(fitness < 0) fitness = 0.1;
    this->fitness = fitness;
    return fitness;
}

double Agent::getFitness(){
    return fitness;
}


double Agent::getMutationValue(double mutationRange){
    double mutationValue = getRandom(0, mutationRange);
    if(getRandom(0,1) <= 0.5) mutationValue *= -1;
    return mutationValue;
}