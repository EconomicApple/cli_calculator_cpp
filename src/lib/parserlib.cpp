#include "parserlib.hpp"

template<typename T>
parserlib::Stack<T>::
Stack()
{
    this->stack_ptr = nullptr;
}

template<typename T>
parserlib::Stack<T>::
~Stack(){}

template<typename T>
parserlib::StackNode<T>::
StackNode()
{
    this->prev = nullptr;
    this->val = T();
}

template<typename T>
parserlib::StackNode<T>::
StackNode(T val)
{
    this->prev = nullptr;
    this->val = val;
}

template<typename T>
parserlib::Stack<T>::
Stack(T val)
{
    this->stack_ptr = std::make_unique<StackNode>(val);
}

template<typename T>
void parserlib::Stack<T>::
push(T val)
{
    
}

// TODO: create operator stack

void parserlib::parse(
    std::vector<lexerlib::Token> tokens)
{
    
}