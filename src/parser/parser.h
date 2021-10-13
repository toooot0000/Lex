#pragma once
#include <iostream>
#include <string>
#include "token.h"

class AST;

class Parser
{
public:
    Parser() = default;
    ~Parser() = default;

    AST * parse();

};