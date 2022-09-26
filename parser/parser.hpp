#include <string>
#include <variant>
#include "tokenbuffer.hpp"
#include "../structure/program.hpp"

class Parser{

    public:
    Parser();
    Program parse(std::string input);
    
    private:
    bool accept();
    bool reject();

    bool matchToken(token_type type);
    bool matchKeyword(std::string keyword);
    bool matchProgram();
    bool matchTerm();
    bool matchEquation();
    bool matchIdentifier();
    bool matchNumber();

    Tokenbuffer tokenbuffer;

    std::variant<EquationNode, TermNode, IdentifierNode, NumericalNode> nodeResult;
    Program programResult;

};