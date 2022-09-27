#include "parser.hpp"

Program Parser::parse(std::string input){
    tokenbuffer = new Tokenbuffer(new Lexer(input));
    if(matchProgram()){
        return *programResult;
    }
    throw std::invalid_argument("Syntax error.");
}

void Parser::init(){
    tokenbuffer->mark();
}

bool Parser::accept(){
    tokenbuffer->unmark();
    return true;
}

bool Parser::reject(){
    tokenbuffer->backtrack();
    return false;
}

bool Parser::matchToken(token_type type){
    init();
    if(tokenbuffer->hasNext()){
        Token token = tokenbuffer->next();
        if(token.type == type){
            return accept();
        }
    }
    return reject();
}

bool Parser::matchKeyword(std::string keyword){
    init();
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
    init();
    if(!matchKeyword("objective")){
        return reject();
    }
    if(!matchToken(COLON)){
        return reject();
    }
    if(!matchTerm()){
        return reject();
    }
    TermNode* objective = get_variant<TermNode>(nodeResult);
    if(!matchToken(SEMICOLON)){
        return reject();
    }
    if(!matchKeyword("constraints")){
        return reject();
    }
    if(!matchToken(COLON)){
        return reject();
    }
    std::list<EquationNode*> constraints;
    while(matchEquation()){
        constraints.emplace_back(get_variant<EquationNode>(nodeResult));
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
    init();
    if(matchOperation() || matchAtom()){
        return accept();
    }
    return reject();
}

/*

    O:
        A+A
        A-A

*/

bool Parser::matchOperation(){
    init();
    if(!matchAtom()){
        return reject();
    }
    AtomNode* term_1 = get_variant<AtomNode>(nodeResult);
    operator_type op;
    if(matchToken(PLUS)){
        op = P;
    }else if(matchToken(MINUS)){
        op = M;
    }else{
        return reject();
    }
    if(!matchTerm()){
        return reject();
    }
    TermNode* term_2 = get_variant<TermNode>(nodeResult);
    nodeResult = new OperationNode(term_1, term_2, op);
    return accept();
}

/*
    A:
        NI

*/

bool Parser::matchAtom(){
    init();
    if(!matchNumber()){
        return reject();
    }
    NumericalNode* numerical = get_variant<NumericalNode>(nodeResult);
    if(!matchIdentifier()){
        return reject();
    }
    IdentifierNode* identifer = get_variant<IdentifierNode>(nodeResult);
    nodeResult = new AtomNode(identifer, numerical);
    return accept();
}

/*

    E:
        A <= A
        A = A
        A >= A
*/

bool Parser::matchEquation(){
    init();
    if(!matchTerm()){
        return reject();
    }
    TermNode* term_1 = get_variant<TermNode>(nodeResult);
    comparer_type cp;
    if(matchToken(LESSEQUAL)){
        cp = LE;
    }else if(matchToken(EQUAL)){
        cp = E;
    }else if(matchToken(GREATEREQUAL)){
        cp = GE;
    }else{
        return reject();
    }
    if(!matchTerm()){
        return reject();
    }
    TermNode* term_2 = get_variant<TermNode>(nodeResult);
    nodeResult = new EquationNode(term_1, term_2, cp);
    return accept();
}

/*

    I:
        {any literal string}
*/
bool Parser::matchIdentifier(){
    init();
    if(tokenbuffer->hasNext()){
        Token token = tokenbuffer->next();
        if(token.type == IDENTIFIER){
            nodeResult = new IdentifierNode(token.value);
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
    init();
    if(tokenbuffer->hasNext()){
        Token token = tokenbuffer->next();
        if(token.type == NUMERICAL){
            nodeResult = new NumericalNode(std::stoi(token.value));
            return accept();
        }
    }
    return reject();
}