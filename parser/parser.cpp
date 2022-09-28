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
        definitions: D; objective: T; constraints: S;
    S:
        E;S
        E;
*/

bool Parser::matchProgram(){
    init();
    if(!matchKeyword("definitions")){
        return reject();
    }
    if(!matchToken(COLON)){
        return reject();
    }
    std::map<std::string, Range> variables;
    while(matchDefinition()){
        variables[std::get<0>(definitionResult)] = std::get<1>(definitionResult); 
        if(!matchToken(SEMICOLON)) return reject();
    }
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
    programResult = new Program(variables, objective, constraints);
    return accept();
}

/*
    D: I:[N,N];
*/

bool Parser::matchDefinition(){
    init();
    if(!matchIdentifier()){
        return reject();
    }
    IdentifierNode* identifier = get_variant<IdentifierNode>(nodeResult);
     if(!matchToken(COLON)){
        return reject();
    }
    if(!matchToken(LBRACKET)){
        return reject();
    }
    if(!matchNumber()){
        return reject();
    }
    NumericalNode* min = get_variant<NumericalNode>(nodeResult);
    if(!matchToken(COMMA)){
        return reject();
    }
    if(!matchNumber()){
        return reject();
    }
    NumericalNode* max = get_variant<NumericalNode>(nodeResult);
    if(!matchToken(RBRACKET)){
        return reject();
    }
    definitionResult = { identifier->getName(), { min->getValue(), max->getValue() }};
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
    operator_type operator_;
    if(matchToken(PLUS)){
        operator_ = P;
    }else if(matchToken(MINUS)){
        operator_ = M;
    }else{
        return reject();
    }
    if(!matchTerm()){
        return reject();
    }
    TermNode* term_2 = get_variant<TermNode>(nodeResult);
    nodeResult = new OperationNode(term_1, term_2, operator_);
    return accept();
}

/*
    A:
        I
        N
        NI

*/

bool Parser::matchAtom(){
    init();
    if(matchConcat() || matchNumber() || matchIdentifier()){
        return accept();
    }
    return reject();
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
    comparator_type comparator_;
    if(matchToken(LESSEQUAL)){
        comparator_ = LE;
    }else if(matchToken(EQUAL)){
        comparator_ = E;
    }else if(matchToken(GREATEREQUAL)){
        comparator_ = GE;
    }else{
        return reject();
    }
    if(!matchTerm()){
        return reject();
    }
    TermNode* term_2 = get_variant<TermNode>(nodeResult);
    nodeResult = new EquationNode(term_1, term_2, comparator_);
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

/*
    C:
        {any concat}
*/
bool Parser::matchConcat(){
    init();
    if(tokenbuffer->hasNext()){
        Token token = tokenbuffer->next();
        if(token.type == NUMERICAL){
            int value = std::stoi(token.value);
            if(tokenbuffer->hasNext()){
                Token token = tokenbuffer->next();
                if(token.type == IDENTIFIER){
                    std::string name = token.value;
                    nodeResult = new ConcatNode(value, name);
                    return accept();
                }
            }
        }
    }
    return reject();
}