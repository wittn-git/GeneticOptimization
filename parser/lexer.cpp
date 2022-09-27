#include "lexer.hpp"

Lexer::Lexer(std::string input) : input(input) {};

Token Lexer::nextToken(){
    if(!hasNextToken()){
        throw std::invalid_argument("No more tokens to parse.");
    }
    std::string slicedInput = input.substr(cursor);
    while(std::regex_search(slicedInput, std::regex("^\\s"))){
        slicedInput = slicedInput.substr(1);
        cursor++;
    }
    for(auto it = specs.begin(); it != specs.end(); it++){
        std::smatch match;
        std::regex_search(slicedInput, match, std::regex("^" + it->first));
        if (match.size() > 0){
            std::string matched_string = match[0];
            cursor += matched_string.length();
            return { it->second, matched_string };
        }
    }
    Token token = { ERROR, slicedInput.substr(0,1) };
    cursor++;
    return token;
}

bool Lexer::hasNextToken(){
    return cursor != input.length();
}

void Lexer::backtrack(int positions){
    cursor = positions;
}

int Lexer::getCursor(){
    return cursor;
}

std::string Lexer::getKeywordregex(){
    std::string regex;
    for(int i=0; i<sizeof(keywords)/sizeof(keywords[0]); i++){
        if(i != 0) regex += "|";
        regex += keywords[i];
    }
    return regex;
}