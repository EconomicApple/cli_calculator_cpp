#include <iostream>
#include "../lib/calculatorlib.hpp"

typedef const char* str_literal_t;

int main(int argc, str_literal_t argv[])
{
    std::cout << "Welcome to CLI Calculator! Enter expression: " << std::endl;

    std::string str;

    while(std::getline(std::cin, str))
    {
        parserlib::TreeNode<lexerlib::Token> syntax_tree = 
              parserlib::syntax_tree(lexerlib::tokenise(str));
        
        std::cout << std::fixed << std::setprecision(4) 
            << calculatorlib::evaluate(syntax_tree) << std::endl;

        std::cout << "Enter expression: " << std::endl;
        break;
    }

    return 0;
}