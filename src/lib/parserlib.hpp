#ifndef TOKENISER_CPP_SRC_LIB_PARSER_HPP
#define TOKENISER_CPP_SRC_LIB_PARSER_HPP

#include "lexerlib.hpp"
#include <memory>

namespace parserlib
{
    struct TokenTypeStackNode
    {
        lexerlib::TokenType type;
        std::unique_ptr<TokenTypeStackNode> prev;

        TokenTypeStackNode();
        TokenTypeStackNode(lexerlib::TokenType type);
    };

    class TokenTypeStack
    {
        private:
            std::unique_ptr<TokenTypeStackNode> stack_ptr;
        public:
            TokenTypeStack();
            ~TokenTypeStack();
            TokenTypeStack(lexerlib::TokenType token_type);
    };

    

    void parse(std::vector<lexerlib::Token> tokens);
};


#endif