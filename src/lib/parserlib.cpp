#include "parserlib.hpp"

std::vector<lexerlib::Token> parserlib::parse(
    const std::vector<lexerlib::Token> &tokens)
{
    std::stack<lexerlib::Token> opstack = {};
    std::vector<lexerlib::Token> outqueue = {};
    // shunting yard
    for (lexerlib::Token token: tokens)
    {
        if (token.is_number())
        {
            outqueue.push_back(token);
        }
        else if (token.is_operator())
        {
            switch(token.get_type())
            {
                case lexerlib::TokenType::kLeftBrac:
                    opstack.push(token);
                    break;
                case lexerlib::TokenType::kRightBrac:
                    while (true)
                    {
                        assert(!opstack.empty());

                        lexerlib::Token token_2 = opstack.top();

                        if (token_2.get_type() 
                            == lexerlib::TokenType::kLeftBrac)
                        {
                            break;
                        }

                        opstack.pop();
                        outqueue.push_back(token_2);
                    }

                    assert(opstack.top().get_type() 
                            == lexerlib::TokenType::kLeftBrac);

                    opstack.pop();
                    break;
                default:
                    while (!opstack.empty() && 
                            opstack.top().get_type() != lexerlib::TokenType::kLeftBrac

                            // assume it is left-associative: does not work with exp
                            && (opstack.top().get_type() <= token.get_type()))
                    {
                        outqueue.push_back(opstack.top());
                        opstack.pop();
                    }

                    opstack.push(token);
                    break;
            }       
        }
    }

    while (!opstack.empty())
    {
        outqueue.push_back(opstack.top());
        opstack.pop();
    }

    return outqueue;
};


template<typename T>
parserlib::TreeNode<T>::TreeNode()
{
    this->val = T();
    this->left = nullptr;
    this->right = nullptr;
}


template<typename T>
parserlib::TreeNode<T>::TreeNode(T val)
{
    this->val = val;
    this->left = nullptr;
    this->right = nullptr;
}

template<typename T>
void parserlib::TreeNode<T>::insert_left_node(T val)
{
    this->left = std::make_shared<TreeNode<T>>(val);
}

template<typename T>
void parserlib::TreeNode<T>::insert_left_treenode(TreeNode<T> val)
{
    this->left = std::make_shared<TreeNode<T>>(val);
}

template<typename T>
void parserlib::TreeNode<T>::insert_right_treenode(TreeNode<T> val)
{
    this->right = std::make_shared<TreeNode<T>>(val);
}


template<typename T>
void parserlib::TreeNode<T>::insert_right_node(T val)
{
    this->right = std::make_shared<TreeNode<T>>(val);
}


int parserlib::
op_precedence(lexerlib::TokenType type)
{
    switch(type)
    {
        case lexerlib::TokenType::kLeftBrac: return LEFTBRAC_PREC;
        case lexerlib::TokenType::kRightBrac: return RIGHTBRAC_PREC;
        case lexerlib::TokenType::kMultiply: return MULTIPLY_PREC;
        case lexerlib::TokenType::kDivide: return DIVIDE_PREC;
        case lexerlib::TokenType::kPlus: return PLUS_PREC;
        case lexerlib::TokenType::kMinus: return MINUS_PREC;
        case lexerlib::TokenType::kAssign: return ASSIGN_PREC;

        default: return NOT_OP;
    }
}

void parserlib::
pop_opstack(std::stack<lexerlib::Token> &opstack,
            std::stack<TreeNode<lexerlib::Token>> &outstack)
{
    // Credit https://stackoverflow.com/a/53920543 CC BY-SA 4.0
    
    assert(!opstack.empty());

    TreeNode<lexerlib::Token> n1(opstack.top());
    opstack.pop();

    assert(!outstack.empty());

    n1.insert_right_treenode(outstack.top());
    outstack.pop();

    assert(!outstack.empty());

    n1.insert_left_treenode(outstack.top());
    outstack.pop();


    outstack.push(n1);
}

parserlib::TreeNode<lexerlib::Token>
parserlib::
syntax_tree(const std::vector<lexerlib::Token> &tokens)
{
    std::stack<lexerlib::Token> opstack = {};
    std::stack<TreeNode<lexerlib::Token>> outstack = {};

    // shunting yard
    for (lexerlib::Token token: tokens)
    {
        if (token.is_number())
        {
            outstack.push(TreeNode<lexerlib::Token>(token));
        }
        else if (token.is_operator())
        {
            switch(token.get_type())
            {
                case lexerlib::TokenType::kLeftBrac:
                    opstack.push(token);
                    break;
                case lexerlib::TokenType::kRightBrac:
                    while (true)
                    {
                        assert(!opstack.empty());

                        if (opstack.top().get_type() 
                            == lexerlib::TokenType::kLeftBrac)
                        {
                            break;
                        }

                        pop_opstack(opstack, outstack);
                    }

                    assert(opstack.top().get_type() 
                            == lexerlib::TokenType::kLeftBrac);

                    opstack.pop();
                    break;
                default:
                    while (!opstack.empty() && 
                            opstack.top().get_type() != lexerlib::TokenType::kLeftBrac

                            // assume it is left-associative: does not work with exp
                            && (opstack.top().get_type() <= token.get_type()))
                    {
                        pop_opstack(opstack, outstack);
                    }

                    opstack.push(token);
                    break;
            }       
        }
    }

    while (!opstack.empty())
    {
        pop_opstack(opstack, outstack);
    }

    assert(outstack.size() == 1);

    return outstack.top();
}

void parserlib::
traverse_print(TreeNode<lexerlib::Token> &tree, int recursion_depth)
{
    for (int i = 0; i < recursion_depth; ++i)
    {
        std::cout << '\t';
    }
    tree.val.print();

    if (tree.left != nullptr)
    {
        traverse_print(*tree.left, recursion_depth + 1);
    }

    if (tree.right == nullptr)
    {
        return;
    }
    traverse_print(*tree.right, recursion_depth + 1);
}

bool parserlib::
operator >(lexerlib::TokenType t1, lexerlib::TokenType t2)
{
    return op_precedence(t1) > op_precedence(t2);
}

bool parserlib::
operator >=(lexerlib::TokenType t1, lexerlib::TokenType t2)
{
    return op_precedence(t1) >= op_precedence(t2);
}


bool parserlib::
operator <(lexerlib::TokenType t1, lexerlib::TokenType t2)
{
    return op_precedence(t1) < op_precedence(t2);
}

bool parserlib::
operator <=(lexerlib::TokenType t1, lexerlib::TokenType t2)
{
    return op_precedence(t1) <= op_precedence(t2);
}