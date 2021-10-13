#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "token.h"

// The lexer class
// Main API is Lexer::next() which will return the next token
namespace Parser{
    class Lexer
    {
    public:
        // Do not use the default constructor;
        Lexer() = delete;
        ~Lexer() = default;

        // Use this instead.
        Lexer(std::istream &in = std::cin);
        
        // Use this instead.
        Lexer(const std::string &in);

        // extract the next token from input stream
        Token next();

        // peek the next token from input stream
        Token peek();

        // Tokenize everything from input
        std::vector<Token> lex(const std::string &in);
        std::vector<Token> lex();

    private:
        // input stream
        std::istream &_input;

        // input string
        std::string _input_string;

        size_t _cur_ind{0};
        size_t _cur_line{0};
        size_t _cur_col{0};

        std::string _match(std::string pattern);
    };
}