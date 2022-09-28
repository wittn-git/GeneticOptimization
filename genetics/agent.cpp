#include "agent.hpp"

Agent::Agent(std::map<std::string, Range> variables){
    for(auto it = variables.begin(); it != variables.end(); it++){
        values[(*it).first] = (*it).second.min;
    }
}

Agent::Agent(std::map<std::string, double> values) : values(values) {};

Agent::Agent(Agent* agent, double mutationRate, double mutationRange){
    std::map<std::string, double> parentValues = agent->getValues();
    for(auto it = parentValues.begin(); it != parentValues.end(); it++){
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

double Agent::calculateFitness(Program* program, std::tuple<double, double> objectiveRange){
    double fitness = 0.1;
    double obj = program->getObjective()->eval(values) + std::get<0>(objectiveRange);
    fitness += (obj * 10)/std::get<1>(objectiveRange);
    std::list<EquationNode*> constraints = program->getConstraints();
    double constraintWeight = 10/constraints.size();
    for(auto it = constraints.begin(); it != constraints.end(); it++){
        if(!std::get<0>((*it)->eval(values))){
            fitness -= constraintWeight;
        }
    }
    if(fitness < 0) fitness = 0;
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