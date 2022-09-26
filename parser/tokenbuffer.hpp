#include <list>
#include "lexer.hpp"

class Tokenbuffer{

    public:
    Tokenbuffer(Lexer lexer);
    Token current();
    Token next();
    void consume();
    void backtrack();
    bool hasNext();

    private:
    Lexer lexer;
    std::list<Token> tokens;
};