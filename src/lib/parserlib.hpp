#ifndef TOKENISER_CPP_SRC_LIB_PARSER_HPP
#define TOKENISER_CPP_SRC_LIB_PARSER_HPP

#include "lexerlib.hpp"
#include <stack>
#include <queue>
#include <cassert>

#define NOT_OP 0
#define LEFTBRAC_PREC 1
#define RIGHTBRAC_PREC 1
#define MULTIPLY_PREC 3
#define DIVIDE_PREC 3
#define PLUS_PREC 4
#define MINUS_PREC 4
#define ASSIGN_PREC 14

namespace parserlib
{
    // Returns precedence. Lower precedence gets executed first.
    bool operator >(lexerlib::TokenType t1, lexerlib::TokenType t2);

    // Returns precedence. Lower precedence gets executed first.
    bool operator >=(lexerlib::TokenType t1, lexerlib::TokenType t2);

    // Returns precedence. Lower precedence gets executed first.
    bool operator <(lexerlib::TokenType t1, lexerlib::TokenType t2);

    // Returns precedence. Lower precedence gets executed first.
    bool operator <=(lexerlib::TokenType t1, lexerlib::TokenType t2);

    int op_precedence(lexerlib::TokenType type);

    // Implementation of shunting yard algorithm
    std::vector<lexerlib::Token> parse(const std::vector<lexerlib::Token> &tokens);
};


#endif