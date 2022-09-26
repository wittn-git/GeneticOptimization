#include "tokenbuffer.hpp"

Tokenbuffer::Tokenbuffer(Lexer lexer) : lexer(lexer) {};

Token Tokenbuffer::current(){
    return tokens.back();
}

Token Tokenbuffer::next(){
    tokens.emplace_back(lexer.nextToken());
    return current();
}

void Tokenbuffer::consume(){
    tokens.erase(tokens.begin());
}

void Tokenbuffer::backtrack(){
    if(!tokens.empty()){
        lexer.backtrack((tokens.back()).value.length());
        tokens.erase(--tokens.end());
    }
}