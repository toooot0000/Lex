#pragma once

#include <string>

// Token can only be moved to another place
namespace Parser
{
    namespace TokenType
    {
        enum Main
        {
            SOF, // start of file
            NEWLINE,
            WHITESPACE,
            INDENT,
            DEDENT,
            IDENTIFIER,
            LITERAL,
            OPERATOR,
            PARENTHESIS,
            END_OF_FILE,
        };

        enum Sub
        {
            EMPTY,
            STRING,
            INTEGER,
            FLOAT,
            ASSIGN,
            COLON,
            ROUND_LEFT,
            ROUND_RIGHT,
            SQUARE_LEFT,
            SQUARE_RIGHT,
            CURLY_LEFT,
            CURLY_RIGHT,
        };
    }

    struct Token
    {

        size_t line_num{0};
        size_t col_num{0};
        size_t start_offset{0};
        size_t end_offset{0};
        TokenType::Main type{TokenType::Main::NEWLINE};
        TokenType::Sub subtype{TokenType::Sub::EMPTY};
        std::string text;

        Token() = default;
        ~Token() = default;

        Token(const Token &other)
            : line_num(other.line_num),
              col_num(other.col_num),
              start_offset(other.start_offset),
              end_offset(other.end_offset),
              type(other.type),
              subtype(other.subtype),
              text(other.text){};
        Token &operator=(const Token &other)
        {
            return *this = Token(other);
        };

        Token(Token &&other) noexcept
            : text(std::move(other.text)),
              type(other.type),
              subtype(other.subtype),
              line_num(other.line_num),
              col_num(other.col_num),
              start_offset(other.start_offset),
              end_offset(other.end_offset)
        {
        }
        Token &operator=(Token &&other) noexcept
        {
            this->text = std::move(other.text);
            this->type = other.type;
            this->subtype = other.subtype;
            this->line_num = other.line_num;
            this->col_num = other.col_num;
            this->start_offset = other.start_offset;
            this->end_offset = other.end_offset;
            return *this;
        };
    };

    static Token make_token(TokenType::Main main_type, size_t start_pos, size_t end_pos, size_t line, size_t col, std::string text = "")
    {
        Token t;
        t.type = main_type;
        t.end_offset = end_pos;
        t.start_offset = start_pos;
        t.line_num = line;
        t.col_num = col;
        t.text = text;
        return t;
    }
}