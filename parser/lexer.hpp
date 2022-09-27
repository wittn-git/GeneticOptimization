#include <string>
#include <map>
#include <regex>
#include <vector>
#include "token.hpp"

class Lexer{

    public:
        Lexer(std::string input);
        //returns next Token after cursor position
        Token nextToken();
        //states if whole input has been lexed
        bool hasNextToken();
        //restores cursor to given position
        void backtrack(int position);
        //returns current cursor position
        int getCursor();

    private:
        std::string input;
        int cursor = 0;
        static std::string getKeywordregex();
        std::map<std::string, token_type> specs = {
            {getKeywordregex(), KEYWORD},
            {"\\d+", NUMERICAL},
            {"(?!"+getKeywordregex()+")[a-zA-Z]+", IDENTIFIER},
            {":", COLON},
            {";", SEMICOLON},
            {"<=", LESSEQUAL},
            {"==", EQUAL},
            {">=", GREATEREQUAL},
            {"\\+", PLUS},
            {"-", MINUS}
    };

};