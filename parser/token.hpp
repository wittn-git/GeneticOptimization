#pragma once
#include <string>

enum token_type { 
    IDENTIFIER, NUMERICAL, ERROR, KEYWORD, COLON, SEMICOLON, LESSEQUAL, 
    EQUAL, GREATEREQUAL, PLUS, MINUS, LBRACKET, RBRACKET, COMMA, LPARENTHESIS, RPARENTHESIS
};
static const char *keywords[] = { "definitions", "objective", "constraints" };
static const char *token_type_str[] = { 
    "IDENTIFIER", "NUMERICAL", "ERROR", "KEYWORD", "COLON", 
    "SEMICOLON", "LESSEQUAL", "EQUAL", "GREATEREQUAL", "PLUS", "MINUS",
    "LBRACKET", "RBRACKET", "COMMA", "LPARENTHESIS",  "RPARENTHESIS"
};

struct Token{
    token_type type;
    std::string value;
};