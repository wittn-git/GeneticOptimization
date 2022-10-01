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
        std::tuple<double, double> getObjectiveRange();
        std::list<std::tuple<double, double>> getConstraintRanges();
    private:
        TermNode* objective;
        std::list<EquationNode*> constraints;
        std::map<std::string, Range> variables;
        std::map<std::string, double> get_mins();
        std::map<std::string, double> get_maxs();
};