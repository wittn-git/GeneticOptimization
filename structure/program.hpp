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
    private:
        TermNode* objective;
        std::list<EquationNode*> constraints;
};