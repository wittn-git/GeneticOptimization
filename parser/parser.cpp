#include "parser.hpp"

Parser::Parser() : tokenbuffer(Lexer("")), nodeResult(Node()) {};

Program* Parser::parse(std::string input){
    Lexer lexer(input);
    this->tokenbuffer = Tokenbuffer(lexer);
    if(matchProgram()){
        return programResult;
    }
    throw std::invalid_argument("Syntax error.");
}

bool Parser::accept(){
    return true;
}

bool Parser::reject(){
    tokenbuffer.backtrack();
    return false;
}

bool Parser::matchToken(token_type type){
    Token token = tokenbuffer.next();
    if(token.type = type){
        return accept();
    }
    return reject();
}

bool Parser::matchKeyword(std::string keyword){
    Token token = tokenbuffer.next();
    if(token.type == KEYWORD && token.value == keyword){
        return accept();
    }
    return reject();
}

/*
    P:
        objective: F; constraints: S;
    S:
        E;S
        E;
*/

bool Parser::matchProgram(){
    if(!matchKeyword("objective")) reject();
    if(!matchToken(COLON)) reject();
    if(!matchTerm()) reject();
    TermNode objective = std::get<TermNode>(nodeResult);
    if(!matchToken(SEMICOLON)) reject();
    if(!matchKeyword("constraints")) reject();
    if(!matchToken(COLON)) reject();
    std::list<EquationNode> constraints;
    while(matchEquation()){
        constraints.emplace_back(nodeResult);
        if(!matchToken(SEMICOLON)) reject();
    }
    if(!matchToken(SEMICOLON)) reject();
    programResult = &Program(objective, constraints);
    return accept();
}

/*
    T:
        NI

*/

bool Parser::matchTerm(){
    if(!matchNumber()) reject();
    NumericalNode numerical = std::get<NumericalNode>(nodeResult);
    if(!matchIdentifier()) reject();
    IdentifierNode identifer = std::get<IdentifierNode>(nodeResult);
    nodeResult = TermNode(identifer, numerical);
    return accept();
}

/*

    E:
        T <= T
        T = T
        T >= T
*/

bool Parser::matchEquation(){
    if(!matchTerm()) reject();
    TermNode term_1 = std::get<TermNode>(nodeResult);;
    operator_type op;
    if(!matchToken(LESSEQUAL)){
        op = LE;
    }else if(!matchToken(EQUAL)){
        op = E;
    }else if(!matchToken(GREATEREQUAL)){
        op = GE;
    }else{
        reject();
    }
    if(!matchTerm()) reject();
    TermNode term_2 =  std::get<TermNode>(nodeResult);
    EquationNode equation(term_1, term_2, op);
    return accept();
}

/*

    I:
        {any literal string}
*/
bool Parser::matchIdentifier(){
    Token token = tokenbuffer.next();
    if(token.type == IDENTIFIER){
        nodeResult = IdentifierNode(token.value);
        return accept();
    }
    return reject();
}

/*
    N:
        {any integer}
*/
bool Parser::matchNumber(){
    Token token = tokenbuffer.next();
    if(token.type == NUMERICAL){
        nodeResult = NumericalNode(std::stoi(token.value));
        return accept();
    }
    return reject();
}