#include <string>
#include <map>
#include <regex>
#include "token.hpp"

class Lexer{

    public:
    Lexer(std::string input);
    Token getNextToken();
    bool hasNextToken();

    private:
    std::string input;
    std::string slicedInput;
    std::map<std::string, token_type> specs = {
        {"^\\d+", NUMERICAL},
        {"^[a-zA-Z]+", IDENTIFIER}
    };

};