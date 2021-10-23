#pragma once
#include <iostream>
#include <string>
#include "token.hpp"

class AST;

namespace Parser
{

    class Parser
    {
    public:
        Parser() = default;
        ~Parser() = default;

        AST *parse();
    };
}