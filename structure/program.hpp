#include <list>
#include "node.hpp"

class Program{
    public:
    Program(TermNode objective, std::list<EquationNode> constraints);
    private:
    TermNode objective;
    std::list<EquationNode> constraints;
};