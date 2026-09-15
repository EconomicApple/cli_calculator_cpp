#include "tokenlib.hpp"

std::vector<tokenlib::Token> tokenlib::
tokenise(const std::string& str)
{
    auto it = str.begin();
    auto it_end = str.end();
    Token token_buf;
    std::vector<Token> tokens = {};
    FilePos pos = FilePos();

    while (it < it_end)
    {
        it = find_next_token(it, it_end, token_buf, pos);

        if (token_buf.get_type() != TokenType::kIllegal)
        {
            tokens.push_back(token_buf);
        }
        else
        {
            throw_illegal_token();
        }
    }

    return tokens;
}


void 
tokenlib::throw_illegal_token()
{
    std::cerr << "Illegal token!" << std::endl;
    exit(EXIT_FAILURE);
}

std::string tokenlib::type_to_string(TokenType type)
{
    switch (type)
    {
        case TokenType::kPlus: return "PLUS";
        case TokenType::kMinus: return "MINUS";
        case TokenType::kMultiply: return "MULTIPLY";
        case TokenType::kDivide: return "DIVIDE";
        case TokenType::kNumber: return "NUMBER";
        default: return "ILLEGAL";
    }
}

void tokenlib::print_token(Token token)
{
    std::cout << "Type: " << std::setw(8) // Left justification
            << std::left << type_to_string(token.get_type()) 
                << " Literal: " << std::setw(8) 
                << std::left << token.get_literal();

    token.get_pos().print();
}



tokenlib::TokenType tokenlib::Token::
get_type()
{
    return this->type;
}

std::string tokenlib::Token::
get_literal()
{
    return this->literal;
}

tokenlib::FilePos tokenlib::Token::
get_pos()
{
    return this->pos;
}


tokenlib::TokenType tokenlib::
char_to_token_type(char c)
{
    switch(c)
    {
        case '+': return TokenType::kPlus;
        case '-': return TokenType::kMinus;
        case '*': return TokenType::kMultiply;
        case '/': return TokenType::kDivide;
    }

    if (isdigit(c)) return TokenType::kNumber;

    return TokenType::kIllegal;
}

bool tokenlib::
is_whitespace(char c)
{
    return (c == ' ' || c == '\n' || c == '\t');
}

tokenlib::FilePos::FilePos()
{
    this->line = 0;
    this->col = 1;
}


void tokenlib::
FilePos::update_file_pos(char c)
{
    if (c == '\n')
    {
        this->col = 1;
        this->line++;
    }
    else
    {
        this->col++;
    }
}

void tokenlib::
FilePos::print()
{
    std::cout << "Line " << this->line << " Col " << this->col << std::endl;
}


std::string::const_iterator tokenlib::
find_next_token(std::string::const_iterator it, 
            std::string::const_iterator it_end, 
            Token &token_buf, FilePos &pos)
{
    // skip whitespace characters
    for (; is_whitespace(*it) && it < it_end; it++)
    {
        pos.update_file_pos(*it);
    }

    FilePos starting_pos = pos;
    
    pos.update_file_pos(*it);

    TokenType start_type = char_to_token_type(*it);

    auto it_start = it++;

    // Continue until token type != start type
    while (it < it_end && char_to_token_type(*it) == start_type)
    {
        pos.update_file_pos(*it);
        it++;
    }

    token_buf = Token(start_type, std::string(it_start, it), starting_pos);

    // return new position of next token to scan
    return it;
}

tokenlib::Token::Token(){}

tokenlib::Token::~Token(){}

tokenlib::Token::Token(TokenType type, std::string literal, FilePos pos)
{
    this->type = type;
    this->literal = literal;
    this->pos = pos;
}


