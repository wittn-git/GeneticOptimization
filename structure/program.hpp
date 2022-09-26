#include <list>
#include <string>
#include <variant>
#include "node.hpp"

class Program{
    public:
    Program(std::variant<AtomNode, OperationNode> objective, std::list<EquationNode> constraints);
    std::string to_string();
    private:
    std::variant<AtomNode, OperationNode> objective;
    std::list<EquationNode> constraints;
};