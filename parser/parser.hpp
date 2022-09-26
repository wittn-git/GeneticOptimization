#include <string>
#include "tokenbuffer.hpp"

class Parser{

    public:
    Parser();
    std::string parse(std::string input);
    
    private:
    bool accept();
    bool reject();

    bool matchToken(token_type type);
    bool matchKeyword(std::string keyword);
    bool matchProgram();
    bool matchIdentifier();
    bool matchNumber();

    Tokenbuffer tokenbuffer;
    std::string result;

};