#pragma once
#include <list>
#include <string>
#include <variant>
#include "node.hpp"

class Program{
    public:
        Program(TermNode* objective, std::list<EquationNode*> constraints);
        std::string to_string();
        TermNode* getObjective();
        std::list<EquationNode*> getConstraints();
        std::set<std::string> getVariableNames();
    private:
        TermNode* objective;
        std::list<EquationNode*> constraints;
        std::set<std::string> variableNames;
};