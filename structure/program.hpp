#include <list>
#include <string>
#include <variant>
#include "node.hpp"

class Program{
    public:
        Program(TermNode* objective, std::list<EquationNode*> constraints);
        std::string to_string();
    private:
        TermNode* objective;
        std::list<EquationNode*> constraints;
};