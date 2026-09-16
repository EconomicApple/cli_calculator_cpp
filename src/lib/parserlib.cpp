#include "parserlib.hpp"

std::vector<lexerlib::Token> parserlib::parse(
    const std::vector<lexerlib::Token> &tokens)
{
    std::stack<lexerlib::Token> opstack = {};
    std::vector<lexerlib::Token> outqueue = {};
    // shunting yard
    for (lexerlib::Token token: tokens)
    {
        if (token.is_number())
        {
            outqueue.push_back(token);
        }
        else if (token.is_operator())
        {
            switch(token.get_type())
            {
                case lexerlib::TokenType::kLeftBrac:
                    opstack.push(token);
                    break;
                case lexerlib::TokenType::kRightBrac:
                    while (true)
                    {
                        assert(!opstack.empty());

                        lexerlib::Token token_2 = opstack.top();

                        if (token_2.get_type() 
                            == lexerlib::TokenType::kLeftBrac)
                        {
                            break;
                        }

                        opstack.pop();
                        outqueue.push_back(token_2);
                    }

                    assert(opstack.top().get_type() 
                            == lexerlib::TokenType::kLeftBrac);

                    opstack.pop();
                    break;
                default:
                    while (!opstack.empty() && 
                            opstack.top().get_type() != lexerlib::TokenType::kLeftBrac
                            && (opstack.top().get_type() <= token.get_type()))
                    {
                        outqueue.push_back(opstack.top());
                        opstack.pop();
                    }

                    opstack.push(token);
                    break;
            }       
        }
    }

    while (!opstack.empty())
    {
        outqueue.push_back(opstack.top());
        opstack.pop();
    }

    return outqueue;
};


int parserlib::
op_precedence(lexerlib::TokenType type)
{
    switch(type)
    {
        case lexerlib::TokenType::kLeftBrac: return LEFTBRAC_PREC;
        case lexerlib::TokenType::kRightBrac: return RIGHTBRAC_PREC;
        case lexerlib::TokenType::kMultiply: return MULTIPLY_PREC;
        case lexerlib::TokenType::kDivide: return DIVIDE_PREC;
        case lexerlib::TokenType::kPlus: return PLUS_PREC;
        case lexerlib::TokenType::kMinus: return MINUS_PREC;
        case lexerlib::TokenType::kAssign: return ASSIGN_PREC;

        default: return NOT_OP;
    }
}

bool parserlib::
operator >(lexerlib::TokenType t1, lexerlib::TokenType t2)
{
    return op_precedence(t1) > op_precedence(t2);
}

bool parserlib::
operator >=(lexerlib::TokenType t1, lexerlib::TokenType t2)
{
    return op_precedence(t1) >= op_precedence(t2);
}


bool parserlib::
operator <(lexerlib::TokenType t1, lexerlib::TokenType t2)
{
    return op_precedence(t1) < op_precedence(t2);
}

bool parserlib::
operator <=(lexerlib::TokenType t1, lexerlib::TokenType t2)
{
    return op_precedence(t1) <= op_precedence(t2);
}