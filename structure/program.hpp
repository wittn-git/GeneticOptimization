#pragma once
#include <list>
#include <string>
#include <variant>
#include "node.hpp"

class Program{
    public:
        Program(std::map<std::string, Range> variables, TermNode* objective, std::list<EquationNode*> constraints);
        std::string to_string();
        TermNode* getObjective();
        std::list<EquationNode*> getConstraints();
        std::map<std::string, Range> getVariables();
    private:
        TermNode* objective;
        std::list<EquationNode*> constraints;
        std::map<std::string, Range> variables;
};