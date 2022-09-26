#include "parser.hpp"

std::string Parser::parse(std::string input){
    Lexer lexer(input);
    std::string temp;
    while(lexer.hasNextToken()){
        auto token = lexer.getNextToken();
        temp += token.value + " " + token_type_str[token.type] + "\n";
    }
    return temp;
}