#include "parser.hpp"

Parser::Parser() : tokenbuffer(Lexer("")) {};

std::string Parser::parse(std::string input){
    Lexer lexer(input);
    this->tokenbuffer = Tokenbuffer(lexer);
    if(matchProgram()){
        return result;
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
        result = token.value;
        return accept();
    }
    return reject();
}

bool Parser::matchKeyword(std::string keyword){
    Token token = tokenbuffer.next();
    if(token.type == KEYWORD && token.value == keyword){
        result = token.value;
        return accept();
    }
    return reject();
}

/*
    P:
        objective: F; constraints: S;
*/

bool Parser::matchProgram(){
    if(!matchKeyword("objective")) reject();
    if(!matchToken(COLON)) reject();
    if(!matchIdentifier()) reject();
    std::string obj = result;
    if(!matchToken(SEMICOLON)) reject();
    if(!matchKeyword("constraints")) reject();
    if(!matchToken(COLON)) reject();
    if(!matchIdentifier()) reject();
    std::string constr = result;
    if(!matchToken(SEMICOLON)) reject();
    result =  "obj " + obj + "; constr " + constr + ";";
    return accept();
}

/*
    I:
        {any literal string}
*/
bool Parser::matchIdentifier(){
    Token token = tokenbuffer.next();
    if(token.type == IDENTIFIER){
        result = token.value;
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
        result = token.value;
        return accept();
    }
    return reject();
}