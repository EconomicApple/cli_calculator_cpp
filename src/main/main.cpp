#include <iostream>
#include "../lib/calculatorlib.hpp"

typedef const char* str_literal_t;

int main(int argc, str_literal_t argv[])
{
    std::string str;
    getline(std::cin, str, {});
    
    parserlib::TreeNode<lexerlib::Token> syntax_tree = 
                parserlib::syntax_tree(lexerlib::tokenise(str));
    
    std::cout << calculatorlib::evaluate(syntax_tree) << std::endl;

    
    return 0;
}