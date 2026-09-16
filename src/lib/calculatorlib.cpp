#include "calculatorlib.hpp"

double calculatorlib::
evaluate(const std::string& str)
{
    return 0;
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