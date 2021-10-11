#include <reflex/input.h>
#include <iostream>
#include <fstream>
#include <string>

#include "parser/parser.hpp"
#include "parser/lex.yy.h"

int main(void)
{
    std::cout << "Start lexing!" << std::endl;
    yy::Lexer lexer((reflex::Input((std::cin))));
    yy::parser parser(lexer);
    parser.parse();
    return 1;
}