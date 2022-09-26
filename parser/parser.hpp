#include <string>
#include <variant>
#include "tokenbuffer.hpp"
#include "../structure/program.hpp"

class Parser{

    public:
    Program parse(std::string input);
    
    private:
    bool accept();
    bool reject();

    bool matchToken(token_type type);
    bool matchKeyword(std::string keyword);
    bool matchProgram();
    bool matchOperation();
    bool matchAtom();
    bool matchTerm();
    bool matchEquation();
    bool matchIdentifier();
    bool matchNumber();

    Tokenbuffer* tokenbuffer;

    std::variant<std::monostate, OperationNode, EquationNode, AtomNode, IdentifierNode, NumericalNode> nodeResult;
    Program* programResult;

};