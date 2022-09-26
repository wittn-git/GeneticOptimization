#include "lexer.hpp"
#include <iostream>

Lexer::Lexer(std::string input) : input(input), slicedInput(input) {};

Token Lexer::getNextToken(){
    if(!hasNextToken()){
        throw std::invalid_argument("No more tokens to parse.");
    }
    while(std::regex_match (slicedInput, std::regex("^\\s"))){
        slicedInput = slicedInput.substr(1);
    }
    for(auto it = specs.begin(); it != specs.end(); it++){
        std::smatch match;
        std::regex_search (slicedInput, match, std::regex(it->first));
        if (match.size() > 0){
            std::string matched_string = match[0];
            slicedInput = slicedInput.substr(matched_string.length());
            return { it->second, matched_string };
        }
    }
    Token token = { ERROR, slicedInput.substr(0,1) };
    slicedInput = slicedInput.substr(1);
    return token;
}

bool Lexer::hasNextToken(){
    return slicedInput.length() != 0;
}