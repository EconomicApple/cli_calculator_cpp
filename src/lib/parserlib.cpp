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
    this->stack_ptr = std::make_unique<StackNode<T>>(val);
}

template<typename T>
void parserlib::Stack<T>::
push(T val)
{
    std::unique_ptr<StackNode<T>> new_ptr = std::make_unique<StackNode<T>>(val);
    new_ptr->prev = std::unique_ptr<StackNode<T>>(this->stack_ptr.release());

    // std::cout << lexerlib::type_to_string(new_ptr->val) << std::endl;

    this->stack_ptr = std::unique_ptr<StackNode<T>>(new_ptr.release());
}


template<typename T>
T parserlib::Stack<T>::
pop()
{
    if (this->stack_ptr != nullptr)
    {
        T val = this->stack_ptr->val;
        this->stack_ptr = this->stack_ptr->prev;
        return val;
    }
    else
    {
        std::cerr << "Stack underflow" << std::endl;
        exit(EXIT_FAILURE);
    }
}



// TODO: create operator stack

void parserlib::parse(
    std::vector<lexerlib::Token> tokens)
{
    
};