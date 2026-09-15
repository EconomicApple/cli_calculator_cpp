#include <iostream>
#include "../lib/tokenlib.hpp"

typedef const char* str_literal_t;

int main(int argc, str_literal_t argv[])
{
    std::string str;
    getline(std::cin, str, {});

    std::vector<tokenlib::Token> tokens = tokenlib::tokenise(str);

    for (auto token: tokens)
    {
        token.print();
    }
    
    return 0;
}