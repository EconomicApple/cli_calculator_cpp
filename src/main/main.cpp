#include <iostream>
#include "../lib/lexerlib.hpp"
#include "../lib/parserlib.hpp"

typedef const char* str_literal_t;

int main(int argc, str_literal_t argv[])
{
    std::string str;
    getline(std::cin, str, {});

    std::vector<lexerlib::Token> tokens = parserlib::parse(
                lexerlib::tokenise(str));

    for (auto token: tokens)
    {
        token.print();
    }
    
    return 0;
}