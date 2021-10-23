#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "token.hpp"

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
        Lexer(std::string in);

        // extract the next token from input stream
        Token next();

        // peek the next token from input stream
        Token peek();

        inline bool reachEnd() const;

        // Tokenize everything from input
        std::vector<Token> lex(const std::string &in);
        std::vector<Token> lex();

    private:
        // input string
        std::string _input_string;

        size_t _cur_ind{0};
        size_t _cur_line{0};
        size_t _cur_col{0};

        Token _cur_tok;

        std::stack<int> _indent_stack;
        size_t _indent_size{0};

        Token handleIndent(size_t start_ind);
        Token handleDedent(size_t start_ind);
        Token handleIdentifier(size_t start_ind);

        bool checkIndentSize();
    };
}