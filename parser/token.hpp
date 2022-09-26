#include <string>

enum token_type { IDENTIFIER, NUMERICAL, ERROR, KEYWORD, COLON, SEMICOLON, LESSEQUAL, EQUAL, GREATEREQUAL};
static const char *keywords[] = { "objective", "constraints" };
static const char *token_type_str[] = { "IDENTIFIER", "NUMERICAL", "ERROR", "KEYWORD", "COLON", "SEMICOLON", "LESSEQUAL", "EQUAL", "GREATEREQUAL" };

struct Token{
    token_type type;
    std::string value;
};