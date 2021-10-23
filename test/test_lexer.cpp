#include <catch2/catch.hpp>
#include <fstream>
#include <sstream>
#include <string>
#include "lexer.h"
#include "token.hpp"

TEST_CASE("Lexer test", "[lexer]")
{
    std::ifstream ifs("test_lexer.in", std::ifstream::in);
    std::stringstream ss;
    ss << ifs.rdbuf();
    std::string in = ss.str();
    Parser::Lexer lexer(in);

    REQUIRE(ifs.good());
    REQUIRE(in == "foo\n    foo\nfoo");

    SECTION("Test Peek")
    {
        auto tk = lexer.peek();
        REQUIRE(tk.type == Parser::TokenType::IDENTIFIER);
        REQUIRE(tk.text == "foo");
        REQUIRE(tk.start_offset == 0);
        REQUIRE(tk.end_offset == 3);
        REQUIRE(tk.col_num == 0);
        REQUIRE(tk.line_num == 0);
    }
    SECTION("Test Next")
    {
        lexer.next();
        auto tk = lexer.peek();
        REQUIRE(tk.type == Parser::TokenType::NEWLINE);
        REQUIRE(tk.text == "\n");
        REQUIRE(tk.start_offset == 3);
        REQUIRE(tk.end_offset == 4);
        REQUIRE(tk.col_num == 0);
        REQUIRE(tk.line_num == 1);
    }
}
