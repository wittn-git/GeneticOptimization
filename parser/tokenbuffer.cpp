#include "tokenbuffer.hpp"

Tokenbuffer::Tokenbuffer(Lexer* lexer) : lexer(lexer) {};

Token Tokenbuffer::current(){
    return tokens.back();
}

Token Tokenbuffer::next(){
    tokens.emplace_back(lexer->nextToken());
    unmarkedTokens.top()++;
    return current();
}

void Tokenbuffer::consume(){
    tokens.erase(tokens.begin());
}

void Tokenbuffer::backtrack(){
    lexer->backtrack(marks.top());
    marks.pop();
    for(int i=0; i<unmarkedTokens.top(); i++){
        tokens.erase(--tokens.end());
    }
    unmarkedTokens.pop();
}

bool Tokenbuffer::hasNext(){
    return lexer->hasNextToken();
}

void Tokenbuffer::unmark(){
    marks.pop();
    unmarkedTokens.pop();
}

void Tokenbuffer::mark(){
    marks.push(lexer->getCursor());
    unmarkedTokens.push(0);
}