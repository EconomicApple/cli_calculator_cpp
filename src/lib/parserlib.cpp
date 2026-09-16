#include "parserlib.hpp"

void parserlib::parse(
    const std::vector<lexerlib::Token> &tokens)
{
    std::stack<lexerlib::Token> opstack = {};
    std::queue<lexerlib::Token> outqueue = {};

    for (lexerlib::Token token: tokens)
    {
        if (token.is_number())
        {
            outqueue.push(token);
        }
        else if (token.is_operator())
        {
            lexerlib::Token token_2 = opstack.top();

            
        }
    }
};