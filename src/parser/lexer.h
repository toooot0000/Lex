#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include "token.hpp"

/** 
 * The lexer class
 * Main API:
 *  Lexer::next(): return next Token and move the inner pointer
 *  Lexer::peek(): return next Token without moving the inner pointer
 *  Lexer::lex():  return a vector of Token parsing every thing from input string    
 */
namespace Parser{
    class Lexer
    {
    public:
        // Default constructor & deconstructor.
        Lexer() = default;
        ~Lexer() = default;

        // Constructor with input string
        Lexer(std::string &in);
        Lexer(std::string &&in);

        // Extract the next token from input stream
        Token next();

        // Peek the next token from input stream
        Token peek() const;

        // Whether there is a next token
        bool hasNext();

        // Tokenize everything from input
        std::vector<Token> lex(const std::string &in);
        std::vector<Token> lex();

        // Getter
        // getStack
        inline std::stack<int> getIndentStack() const noexcept { return _indent_stack; }
        inline Token getCurTok() const noexcept { return _cur_tok; }
        inline char getCurChar() const noexcept { return _cur_ind < _input_string.size() ? _input_string[_cur_ind] : ' '; }

    private:
        // Input string
        std::string _input_string;

        size_t _cur_ind{0};
        size_t _cur_line{0};
        size_t _cur_col{0};

        // Current Token
        Token _cur_tok;

        // Used to determine indents and dedents
        std::stack<int> _indent_stack;
        size_t _indent_size{0};

        // Whether reaching eof
        inline bool reachEnd() const;

        // Remove empty lines and redundant leading or trailing "\n"s
        void prepareInput();

        // Return the next Token
        Token extractNext();

        Token handleIndent(size_t start_ind);
        Token handleDedent(size_t start_ind);
        Token handleIdentifier(size_t start_ind);
    };
}