#include "program.hpp"

Program::Program(TermNode* objective, std::list<EquationNode*> constraints) : objective(objective), constraints(constraints) {
    variableNames = objective->getVariables();
    for(auto it = constraints.begin(); it != constraints.end(); ++it){
        std::set<std::string> v2 = (*it)->getVariables();
        variableNames.insert(v2.begin(), v2.end());
    }
};

std::string Program::to_string(){
    std::string program_string;
    program_string += "objective:\n";
    program_string += objective->to_string() + "\n";
    program_string += "constraints:\n";
    for(auto it = constraints.begin(); it != constraints.end(); it++){
        program_string += (*it)->to_string()  + "\n";
    }
    return program_string;
}

TermNode* Program::getObjective(){
    return objective;
}

std::list<EquationNode*> Program::getConstraints(){
    return constraints;
}

std::set<std::string> Program::getVariableNames(){
    return variableNames;
}