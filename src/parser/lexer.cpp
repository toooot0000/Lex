#include "lexer.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>

namespace Parser
{
    using namespace std;


    Lexer::Lexer(istream &in)
        : _input(in), _input_string(string())
    {}

    Lexer::Lexer(const string &in)
        : _input_string(in), _input(cin)
    {}

    vector<Token> Lexer::lex()
    {
        return lex(_input_string);
    }

    vector<Token> Lexer::lex(const string &in)
    {
        size_t i{0};
        size_t cur_line{0};
        size_t cur_col{0};

        size_t indent_size{0};
        stack<size_t> indent_stack({0});
        

        vector<Token> ret;
        Token curTok;
        

        while(i < in.size())
        {
            auto ch = in[i];
            switch(ch)
            {
            case ' ':
            {
                switch (curTok.type)
                {
                case TokenType::SOF:
                {
                    cerr << "First line start with blank space" << endl;
                    throw runtime_error("The first line start with blank space");
                    break;
                }
                
                case TokenType::NEWLINE:
                {
                    ret.emplace_back(move(curTok));
                    curTok = Token();
                    curTok.start_offset = i;

                    size_t j = i;
                    int tab_num = 0;
                    while(j<in.size() && (in[j] == ' ' || in[j] == '\t'))
                    {
                        if(in[j] == '\t') tab_num ++ ; // replace tab to 4 white space
                        j++;
                        cur_col++;
                    }
                    curTok.end_offset = j;
                    if(j < in.size() && in[j] == '\r' || in[j] == '\n')
                    {
                        curTok.type = TokenType::WHITESPACE;
                    }
                    else
                    {
                        auto last_indent = indent_stack.top();
                        auto whitespace_num = j - i + tab_num * 3;

                        if(whitespace_num > last_indent)
                        {
                            if(indent_size == 0)
                                indent_size = whitespace_num;
                            else if(indent_size + last_indent != whitespace_num)
                                throw runtime_error("Wrong number of white space!");
                            
                            indent_stack.push(whitespace_num);

                            curTok.type = TokenType::INDENT;
                            ret.emplace_back(move(curTok));

                            curTok = Token();
                            curTok.type = TokenType::WHITESPACE;
                            curTok.start_offset = j;
                        }
                        else if(whitespace_num == last_indent)
                        {
                            curTok.type = TokenType::WHITESPACE;
                            curTok.end_offset = j;
                        }
                        else
                        {
                            while(indent_stack.top() > whitespace_num)
                            {
                                indent_stack.pop();
                                curTok.type = TokenType::DEDENT;
                                ret.emplace_back(move(curTok));
                                curTok = Token();
                            }
                            curTok.type = TokenType::WHITESPACE;
                            curTok.start_offset = j;
                            if(indent_stack.top() != whitespace_num)
                                throw runtime_error("Wrong Indent!");

                        }
                    }
                    i = j;
                    break;
                }

                case TokenType::WHITESPACE:
                {
                    i++;
                    cur_col++;
                    break;
                }
                
                default:
                {
                    curTok.end_offset = i;
                    ret.emplace_back(move(curTok));
                    curTok = make_token(TokenType::WHITESPACE, i);
                    i++;
                    cur_col++;
                    break;
                }
                }
                break;
            }
                

            case '\r':
            case '\n':{
                if(curTok.type != TokenType::SOF)
                {
                    if(curTok.type != TokenType::WHITESPACE)
                        ret.emplace_back(move(curTok));
                    curTok = make_token(TokenType::NEWLINE, i);
                    curTok.text = ch;
                }
                cur_line++;
                cur_col = 0;
                i++;
                break;
            }
            
            case '(':
            case ')':
            case '[':
            case ']':
            case '{':
            case '}':
            {
                if(curTok.type != TokenType::WHITESPACE)
                {
                    ret.emplace_back(move(curTok));
                }
                curTok = make_token(TokenType::PARENTHESIS, i);
                curTok.text = ch;
                i++;
                cur_col++;
                break;
            }


            case '=':
            case ':':
            case '.':
            case '/':
            case '*':
            case '-':
            case '+':
            {
                if(curTok.type != TokenType::WHITESPACE)
                {
                    ret.emplace_back(move(curTok));
                }
                curTok = make_token(TokenType::OPERATOR, i);
                curTok.text = ch;
                i++;
                cur_col++;
                break;
            }
            
            case 'A' ... 'Z':
            case 'a' ... 'z':
                i++;
                break;

            case '0' ... '9':
                switch (curTok.type)
                {
                case TokenType::Main::IDENTIFIER:
                case TokenType::Main::LITERAL:
                    curTok.text.append(1, ch);
                    curTok.end_offset++;
                    break;
                
                case TokenType::Main::WHITESPACE:
                    
                    break;

                default:
                    break;
                }
                i++;
                cur_col++;
                break;
            }
        }
        return ret; 
    }

} // namespace Parser


