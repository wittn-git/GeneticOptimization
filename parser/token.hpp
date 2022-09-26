#include <string>

enum token_type { IDENTIFIER, NUMERICAL, ERROR };
static const char *token_type_str[] = { "IDENTIFIER", "NUMERICAL", "ERROR" };

struct Token{
    token_type type;
    std::string value;
};