#include <string>

enum token_type { 
    IDENTIFIER, NUMERICAL, ERROR, KEYWORD, COLON, SEMICOLON, LESSEQUAL, 
    EQUAL, GREATEREQUAL, PLUS, MINUS 
};
static const char *keywords[] = { "objective", "constraints" };
static const char *token_type_str[] = { 
    "IDENTIFIER", "NUMERICAL", "ERROR", "KEYWORD", "COLON", 
    "SEMICOLON", "LESSEQUAL", "EQUAL", "GREATEREQUAL", "PLUS", "MINUS" 
};

struct Token{
    token_type type;
    std::string value;
};