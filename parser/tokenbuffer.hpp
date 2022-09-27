#include <list>
#include <stack>
#include "lexer.hpp"

class Tokenbuffer{

    public:
        Tokenbuffer(Lexer *lexer);
        Token current();
        Token next();
        void consume();
        void backtrack();
        bool hasNext();
        void mark();
        void unmark();

    private:
        Lexer* lexer;
        std::list<Token> tokens;
        std::stack<int> marks, unmarkedTokens;
        
};