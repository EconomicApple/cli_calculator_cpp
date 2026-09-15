#include "parserlib.hpp"

parserlib::TokenTypeStack::
TokenTypeStack()
{
    this->stack_ptr = nullptr;
}

parserlib::TokenTypeStack::
~TokenTypeStack(){}

parserlib::TokenTypeStackNode::
TokenTypeStackNode()
{
    this->prev = nullptr;
    this->type = lexerlib::TokenType::kIllegal;
}

parserlib::TokenTypeStackNode::
TokenTypeStackNode(lexerlib::TokenType type)
{
    this->prev = nullptr;
    this->type = type;
}

parserlib::TokenTypeStack::
TokenTypeStack(lexerlib::TokenType token_type)
{
    this->stack_ptr = std::make_unique<TokenTypeStackNode>(token_type);
}

// TODO: create operator stack

void parserlib::parse(
    std::vector<lexerlib::Token> tokens)
{
    
}