#ifndef TOKENISER_CPP_SRC_LIB_PARSER_HPP
#define TOKENISER_CPP_SRC_LIB_PARSER_HPP

#include "lexerlib.hpp"
#include <stack>
#include <queue>
#include <cassert>

#define NOT_OP 0
#define LEFTBRAC_PREC 1
#define RIGHTBRAC_PREC 1
#define MULTIPLY_PREC 3
#define DIVIDE_PREC 3
#define PLUS_PREC 4
#define MINUS_PREC 4
#define ASSIGN_PREC 14

#include <memory>
namespace parserlib
{

template<typename T>
struct TreeNode
{
    T val;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;

    TreeNode();
    TreeNode(T val);

    void insert_left_node(T val);
    void insert_right_node(T val);

    void insert_left_treenode(TreeNode<T> val);
    void insert_right_treenode(TreeNode<T> val);
};


// Prints all tokens in AST
void traverse_print(TreeNode<lexerlib::Token> &tree, int recursion_depth);


// Returns precedence. Lower precedence gets executed first.
bool operator >(lexerlib::TokenType t1, lexerlib::TokenType t2);

// Returns precedence. Lower precedence gets executed first.
bool operator >=(lexerlib::TokenType t1, lexerlib::TokenType t2);

// Returns precedence. Lower precedence gets executed first.
bool operator <(lexerlib::TokenType t1, lexerlib::TokenType t2);

// Returns precedence. Lower precedence gets executed first.
bool operator <=(lexerlib::TokenType t1, lexerlib::TokenType t2);

int op_precedence(lexerlib::TokenType type);

void pop_opstack(std::stack<lexerlib::Token> &opstack, 
                std::stack<TreeNode<lexerlib::Token>> &outstack);

// Implementation of shunting yard algorithm (Postfix)
std::vector<lexerlib::Token> parse(const std::vector<lexerlib::Token> &tokens);

// Implementation of shunting yard algorithm (Abstract search tree)
TreeNode<lexerlib::Token> syntax_tree(const std::vector<lexerlib::Token> &tokens);
};


#endif