#include <catch2/catch.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include "lexer.h"
#include "token.hpp"

std::string getContent(std::string &&filename)
{
    std::ifstream ifs(filename, std::ifstream::in);
    if (!ifs.is_open())
    {
        throw std::runtime_error("File Error: File not open!");
    }
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string in = ss.str();
    return in;
}

TEST_CASE("LexerNormal", "[lexer]")
{
    Parser::Lexer lexer(getContent("test_lexer.in"));

    SECTION("Test Peek")
    {
        auto tk = lexer.peek();
        REQUIRE(tk.type == Parser::TokenType::NEWLINE);
    }
    // !SECTION
    SECTION("Test Next")
    {
        lexer.next();
        auto tk = lexer.peek();
        REQUIRE(tk.type == Parser::TokenType::IDENTIFIER);
    }
    // !SECTION
    SECTION("Test Dedent and hasNext")
    {
        lexer.next(); // "\n"
        lexer.next(); // "foo"
        lexer.next(); // "\n"
        lexer.next(); // "    "
        REQUIRE(lexer.getIndentStack().top() == 4);
        lexer.next();           // "foo"
        lexer.next();           // "\n"
        auto tk = lexer.next(); // "foo"
        INFO(tk.toString());
        REQUIRE(tk.type == Parser::TokenType::DEDENT);
        tk = lexer.next();
        REQUIRE(tk.type == Parser::TokenType::IDENTIFIER);
        // Throw runtime error
        REQUIRE_THROWS(tk = lexer.next());
        REQUIRE(!lexer.hasNext());
    }
    // !SECTION
}

TEST_CASE("LexerLex", "[lexer]")
{
    Parser::Lexer lexer(getContent("test_lexer.in"));
    auto ret = lexer.lex();
    CHECK(ret.size() > 0);

    for (auto tk : ret)
    {
        UNSCOPED_INFO(tk.toString());
    }
    CHECK(false);
}

TEST_CASE("LexerMixed", "[lexer]")
{
    std::string in = getContent("test_lexer_mixedIdentifiers.in");
    INFO(in);
    Parser::Lexer lexer(in);
    auto ret = lexer.lex();
    CHECK(ret.size() > 0);

    for (auto tk : ret)
    {
        UNSCOPED_INFO(tk.toString());
    }
    CHECK(false);
}

TEST_CASE("LexerMulti", "[lexer]")
{
    std::string in = getContent("test_lexer_multiIndents.in");
    INFO(in);
    Parser::Lexer lexer(in);
    auto ret = lexer.lex();
    CHECK(ret.size() > 0);

    for (auto tk : ret)
    {
        UNSCOPED_INFO(tk.toString());
    }
    CHECK(false);
}