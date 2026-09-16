#ifndef TOKENISER_CPP_SRC_LIB_LEXERLIB_HPP
#define TOKENISER_CPP_SRC_LIB_LEXERLIB_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>

#define FORMAT_WIDTH 12

#define PLUS "PLUS"
#define MINUS "MINUS"
#define MULTIPLY "MULTIPLY"
#define DIVIDE "DIVIDE"
#define NUMBER "NUMBER"
#define IDENTIFIER "IDENTIFIER"
#define SEMICOLON "SEMICOLON"
#define ASSIGN "ASSIGN"
#define ILLEGAL "ILLEGAL"
#define LEFTBRAC "LEFTBRAC"
#define RIGHTBRAC "RIGHTBRAC"

#define NOT_OP 0
#define LEFTBRAC_PREC 1
#define RIGHTBRAC_PREC 1
#define MULTIPLY_PREC 3
#define DIVIDE_PREC 3
#define PLUS_PREC 4
#define MINUS_PREC 4


namespace lexerlib
{
    enum class TokenType
    {
        kIllegal,
        kLeftBrac,
        kRightBrac,
        kPlus,
        kMinus,
        kMultiply,
        kDivide,
        kIdentifier,
        kAssign,
        kSemicolon,
        kNumber
    };

    int op_precedence(TokenType type);

    bool is_whitespace(char c);
    TokenType char_to_token_type(char c);

    struct FilePos
    {
        int line;
        int col;

        FilePos();

        // Use every time getchar() is used to keep track of file location.
        void update_file_pos(char c);
        void print();
    };

    class Token
    {
        private:
            TokenType type;
            std::string literal;
            FilePos pos;

            // Puts next token in token_buf and returns new pointer to string
            
        public:
            Token();
            ~Token();
            Token(TokenType type, std::string literal, FilePos pos);
            TokenType get_type();
            std::string get_literal();  
            FilePos get_pos();
            bool is_operator();
            bool is_number();
            void print();
    };

    double operator *(Token t1, Token t2);


    std::vector<Token> tokenise(const std::string &str);

    std::string::const_iterator find_next_token(std::string::const_iterator it, 
                        std::string::const_iterator it_end,
                            Token &token_buf, FilePos &pos);

    void throw_illegal_token();

    std::string type_to_string(TokenType type);
};



#endif