#ifndef TOKENISER_CPP_SRC_LIB_TOKENLIB_HPP
#define TOKENISER_CPP_SRC_LIB_TOKENLIB_HPP

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>

namespace tokenlib
{

    enum class TokenType
    {
        kIllegal,
        kPlus,
        kMinus,
        kMultiply,
        kDivide,
        kNumber
    };

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
    };

    std::vector<Token> tokenise(const std::string &str);

    std::string::const_iterator find_next_token(std::string::const_iterator it, 
                        std::string::const_iterator it_end,
                            Token &token_buf, FilePos &pos);

    void throw_illegal_token();

    std::string type_to_string(TokenType type);
    void print_token(Token token);
};



#endif