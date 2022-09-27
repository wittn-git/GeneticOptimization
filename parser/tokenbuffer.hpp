#include <list>
#include <stack>
#include "lexer.hpp"

class Tokenbuffer{

    public:
        Tokenbuffer(Lexer *lexer);
        //returns current token
        Token current();
        //returns next token
        Token next();
        //consumes current token
        void consume();
        //restores buffer and lexer state to last mark
        void backtrack();
        //states if whole input has been lexed
        bool hasNext();
        //saves current buffer and lexer state
        void mark();
        //removes last save of current buffer and lexer state
        void unmark();

    private:
        Lexer* lexer;
        std::list<Token> tokens;
        std::stack<int> marks, unmarkedTokens;
        
};