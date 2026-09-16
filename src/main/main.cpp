#include <iostream>
#include "../lib/calculatorlib.hpp"

typedef const char* str_literal_t;

int main(int argc, str_literal_t argv[])
{
    std::string str;
    getline(std::cin, str, {});
    
    parserlib::TreeNode<lexerlib::Token> tree = 
                parserlib::syntax_tree(lexerlib::tokenise(str));

    parserlib::traverse_print(tree, 0);
    
    return 0;
}