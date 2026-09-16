#ifndef TOKENISER_CPP_SRC_LIB_CALCULATORLIB_HPP
#define TOKENISER_CPP_SRC_LIB_CALCULATORLIB_HPP

#include "parserlib.hpp"

namespace calculatorlib
{
    double evaluate(parserlib::TreeNode<lexerlib::Token> &tree);

    double operator *(lexerlib::Token t1, lexerlib::Token t2);
    double operator /(lexerlib::Token t1, lexerlib::Token t2);
    double operator +(lexerlib::Token t1, lexerlib::Token t2);
    double operator -(lexerlib::Token t1, lexerlib::Token t2);
}

#endif