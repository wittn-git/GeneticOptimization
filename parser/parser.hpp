#pragma once
#include <string>
#include "tokenbuffer.hpp"
#include "../structure/program.hpp"
#include "../util/variant_util.hpp"

class Parser{

    public:
        //parses program from given input string
        Program parse(std::string input);
    
    private:
        void init();
        bool accept();
        bool reject();

        bool matchToken(token_type type);
        bool matchKeyword(std::string keyword);
        bool matchProgram();
        bool matchDefinition();
        bool matchOperation();
        bool matchAtom();
        bool matchTerm();
        bool matchEquation();
        bool matchIdentifier();
        bool matchNumerical();
        bool matchConcat();

        Tokenbuffer* tokenbuffer;

        std::variant<OperationNode*, EquationNode*, IdentifierNode*, NumericalNode*, TermNode*> nodeResult;
        std::tuple<std::string, Range> definitionResult;
        Program* programResult;

};