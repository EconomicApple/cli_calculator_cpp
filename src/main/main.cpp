#include <iostream>
#include "../lib/tokenlib.hpp"

typedef const char* str_literal_t;

int main(int argc, str_literal_t argv[])
{
    if (argc <= 1) return 0;
    
    std::vector<tokenlib::Token> tokens = tokenlib::tokenise(argv[1]);

    for (auto token: tokens)
    {
        tokenlib::print_token(token);
    }
    
    return 0;
}