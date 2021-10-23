#include "lexer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <regex>

namespace Parser
{
    using namespace std;

    Lexer::Lexer(string in)
        : _input_string(in)
    {
        _indent_stack.push(0);
    }

    vector<Token> Lexer::lex()
    {
        return lex(_input_string);
    }

    vector<Token> Lexer::lex(const string &in)
    {
        vector<Token> ret;
        return ret;
    }

    Token Lexer::next()
    {
        Token ret = _cur_tok;
        _cur_tok = peek();
        if (_cur_tok.type == TokenType::DEDENT)
        {
            _indent_stack.pop();
        }
        _cur_ind = _cur_tok.end_offset;
        return ret;
    }

    Token Lexer::peek()
    {
        Token next;
        switch (_input_string[_cur_ind])
        {
        case ' ':
            switch (_cur_tok.type)
            {
            case TokenType::NEWLINE:
                next = handleIndent(_cur_ind);
                break;

            case TokenType::DEDENT:
                next = handleDedent(_cur_ind);
                break;

            default:

                break;
            }
            break;

        case '\r':
        case '\n':
            next = make_token(TokenType::NEWLINE,
                              _cur_ind,
                              _cur_ind + 1,
                              _cur_line + 1,
                              0, "\n");
            break;

        case '_':
        case 'A' ... 'Z':
        case 'a' ... 'z':
            next = handleIdentifier(_cur_ind);
            break;

        default:
            break;
        }
        return next;
    }

    Token Lexer::handleIndent(size_t start_ind)
    {
        Token next;
        int i = start_ind;
        while (i < _input_string.size() && _input_string[i] == ' ')
        {
            i++;
        }
        int num_blankspace = i - start_ind;
        if (i < _input_string.size() && (_input_string[i] == '\n' || _input_string[i] == '\r'))
        {
            next = make_token(TokenType::NEWLINE,
                              start_ind,
                              i,
                              _cur_tok.line_num + 1,
                              0, "\n");
        }
        else if (num_blankspace > _indent_stack.top())
        {
            if (_indent_size == 0)
            {
                _indent_size = num_blankspace;
            }
            if (num_blankspace % _indent_size != 0)
            {
                // send error
                throw runtime_error("Wrong indent size!");
            }
            next = make_token(TokenType::INDENT,
                              start_ind,
                              i,
                              _cur_tok.line_num,
                              _cur_tok.col_num + num_blankspace);
        }
        else if (num_blankspace == _indent_stack.top())
        {
            next = handleIdentifier(i);
        }
        else
        {
            next = make_token(TokenType::DEDENT,
                              start_ind,
                              start_ind,
                              _cur_tok.line_num,
                              _cur_tok.col_num);
        }

        return next;
    }

    Token Lexer::handleDedent(size_t start_ind)
    {
        Token next;
        int i = start_ind;
        while (i < _input_string.size() && _input_string[i] == ' ')
        {
            i++;
        }
        int num_blankspace = i - start_ind;
        if (num_blankspace > _indent_stack.top())
        {
            throw runtime_error("Wrong dedent size!");
        }
        else if (num_blankspace == _indent_stack.top())
        {
            next = handleIdentifier(i);
        }
        else
        {
            next = make_token(TokenType::DEDENT,
                              start_ind,
                              start_ind,
                              _cur_tok.line_num,
                              _cur_tok.col_num);
        }

        return next;
    }

    Token Lexer::handleIdentifier(size_t start_ind)
    {
        Token next = make_token(TokenType::IDENTIFIER, start_ind, start_ind + 1, _cur_line, _cur_col, string(1, _input_string[start_ind]));
        int i = start_ind + 1;
        regex pattern("[a-zA-Z_][a-zA-Z0-9_]*");
        while (i < _input_string.size() && regex_match(next.text + _input_string[i], pattern))
        {
            next.text.append(1, _input_string[i]);
            i++;
        }
        next.end_offset = i;
        return next;
    }

    inline bool Lexer::reachEnd() const
    {
        return _cur_ind >= _input_string.size();
    }
} // namespace Parser
