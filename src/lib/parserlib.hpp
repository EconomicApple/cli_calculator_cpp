#ifndef TOKENISER_CPP_SRC_LIB_PARSER_HPP
#define TOKENISER_CPP_SRC_LIB_PARSER_HPP

#include "lexerlib.hpp"
#include <memory>

namespace parserlib
{
    template<typename T>
    struct StackNode
    {
        T val;
        std::unique_ptr<StackNode> prev;

        StackNode();
        StackNode(T val);
    };

    template<typename T>
    class Stack
    {
        private:
            std::unique_ptr<StackNode<T>> stack_ptr;
        public:
            Stack();
            ~Stack();
            Stack(T val);
            void push(T val);
            T pop();
    };

    

    void parse(std::vector<lexerlib::Token> tokens);
};


#endif