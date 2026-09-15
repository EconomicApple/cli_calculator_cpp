#ifndef TOKENISER_CPP_SRC_LIB_PARSER_HPP
#define TOKENISER_CPP_SRC_LIB_PARSER_HPP

#include "lexerlib.hpp"
#include <memory>
#include <stack>
#include <queue>

namespace parserlib
{
    void parse(const std::vector<lexerlib::Token> &tokens);
};


#endif