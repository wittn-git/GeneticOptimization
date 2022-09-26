#include "parser.hpp"

Program Parser::parse(std::string input){
    tokenbuffer = new Tokenbuffer(new Lexer(input));
    if(matchProgram()){
        return *programResult;
    }
    throw std::invalid_argument("Syntax error.");
}

bool Parser::accept(){
    return true;
}

bool Parser::reject(){
    tokenbuffer->backtrack();
    return false;
}

bool Parser::matchToken(token_type type){
    if(tokenbuffer->hasNext()){
        Token token = tokenbuffer->next();
        if(token.type == type){
            return accept();
        }
    }
    return reject();
}

bool Parser::matchKeyword(std::string keyword){
    if(tokenbuffer->hasNext()){
        Token token = tokenbuffer->next();
        if(token.type == KEYWORD && token.value == keyword){
            return accept();
        }
    }   
    return reject();
}

/*
    P:
        objective: T; constraints: S;
    S:
        E;S
        E;
*/

bool Parser::matchProgram(){
    if(!matchKeyword("objective")) return reject();
    if(!matchToken(COLON)) return reject();
    if(!matchTerm()) return reject();
    std::variant<AtomNode, OperationNode> objective = std::get<std::variant<AtomNode, OperationNode>>(nodeResult);
    if(!matchToken(SEMICOLON)) return reject();
    if(!matchKeyword("constraints")) return reject();
    if(!matchToken(COLON)) return reject();
    std::list<EquationNode> constraints;
    while(matchEquation()){
        constraints.emplace_back(std::get<EquationNode>(nodeResult));
        if(!matchToken(SEMICOLON)) return reject();
    }
    programResult = new Program(objective, constraints);
    return accept();
}

/*
    T:
        O
        A

*/

bool Parser::matchTerm(){
    if(matchOperation() || matchAtom()){
        accept();
    }
    return reject();
}

/*

    O:
        A+A
        A-A

*/

bool Parser::matchOperation(){
    if(!matchAtom()) reject();
    AtomNode atom_1 = std::get<AtomNode>(nodeResult);
    operator_type op;
    if(matchToken(PLUS)) op = P;
    else if(matchToken(MINUS)) op = M;
    else reject();
    if(!matchAtom()) reject();
    AtomNode atom_2 = std::get<AtomNode>(nodeResult);
    nodeResult = OperationNode(atom_1, atom_2, op);
    accept();
}

/*
    A:
        NI

*/

bool Parser::matchAtom(){
    if(!matchNumber()) return reject();
    NumericalNode numerical = std::get<NumericalNode>(nodeResult);
    if(!matchIdentifier()) return reject();
    IdentifierNode identifer = std::get<IdentifierNode>(nodeResult);
    AtomNode atom_1 = AtomNode(identifer, numerical);
    operator_type op;
    return accept();
}

/*

    E:
        A <= A
        A = A
        A >= A
*/

bool Parser::matchEquation(){
    if(!matchTerm()) return reject();
    AtomNode atom_1 = std::get<AtomNode>(nodeResult);
    comparer_type cp;
    if(matchToken(LESSEQUAL)) cp = LE;
    else if(matchToken(EQUAL)) cp = E;
    else if(matchToken(GREATEREQUAL)) cp = GE;
    else return reject();
    if(!matchTerm()) return reject();
    AtomNode atom_2 = std::get<AtomNode>(nodeResult);
    nodeResult = EquationNode(atom_1, atom_2, cp);
    return accept();
}

/*

    I:
        {any literal string}
*/
bool Parser::matchIdentifier(){
    if(tokenbuffer->hasNext()){
        Token token = tokenbuffer->next();
        if(token.type == IDENTIFIER){
            nodeResult = IdentifierNode(token.value);
            return accept();
        }
    }
    return reject();
}

/*
    N:
        {any integer}
*/
bool Parser::matchNumber(){
    if(tokenbuffer->hasNext()){
        Token token = tokenbuffer->next();
        if(token.type == NUMERICAL){
            nodeResult = NumericalNode(std::stoi(token.value));
            return accept();
        }
    }
    return reject();
}