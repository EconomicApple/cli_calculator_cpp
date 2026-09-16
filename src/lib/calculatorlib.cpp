#include "calculatorlib.hpp"

double calculatorlib::
evaluate(parserlib::TreeNode<lexerlib::Token> &tree)
{
    if (tree.left == nullptr || tree.right == nullptr && tree.val.is_number())
    {
        return std::stod(tree.val.get_literal());
    }

    switch(tree.val.get_type())
    {
        case lexerlib::TokenType::kMultiply:
            return (evaluate(*(tree.left)) * evaluate(*(tree.right)));
        case lexerlib::TokenType::kDivide:
            return (evaluate(*(tree.left)) / evaluate(*(tree.right)));
        case lexerlib::TokenType::kPlus:
            return (evaluate(*(tree.left)) + evaluate(*(tree.right)));
        case lexerlib::TokenType::kMinus:
            return (evaluate(*(tree.left)) - evaluate(*(tree.right)));
        default:
            lexerlib::throw_illegal_token();
            // pacify compiler
            return 0;
    }
}

double 
calculatorlib::operator *(lexerlib::Token t1, lexerlib::Token t2)
{
    if (!(t1.is_number() && t2.is_number()))
    {
        lexerlib::throw_illegal_token();
    }

    return std::stod(t1.get_literal()) * std::stod(t2.get_literal());
}


double 
calculatorlib::operator /(lexerlib::Token t1, lexerlib::Token t2)
{
    if (!(t1.is_number() && t2.is_number()))
    {
        lexerlib::throw_illegal_token();
    }

    return std::stod(t1.get_literal()) / std::stod(t2.get_literal());
}


double 
calculatorlib::operator +(lexerlib::Token t1, lexerlib::Token t2)
{
    if (!(t1.is_number() && t2.is_number()))
    {
        lexerlib::throw_illegal_token();
    }

    return std::stod(t1.get_literal()) + std::stod(t2.get_literal());
}

double 
calculatorlib::operator -(lexerlib::Token t1, lexerlib::Token t2)
{
    if (!(t1.is_number() && t2.is_number()))
    {
        lexerlib::throw_illegal_token();
    }

    return std::stod(t1.get_literal()) - std::stod(t2.get_literal());
}