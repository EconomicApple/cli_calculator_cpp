#include "lexerlib.hpp"

std::vector<lexerlib::Token> lexerlib::
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
lexerlib::throw_illegal_token()
{
    std::cerr << "Illegal token!" << std::endl;
    exit(EXIT_FAILURE);
}

std::string lexerlib::type_to_string(TokenType type)
{
    switch (type)
    {
        case TokenType::kPlus: return LEXERLIB_PLUS_LITERAL;
        case TokenType::kMinus: return LEXERLIB_MINUS_LITERAL;
        case TokenType::kMultiply: return LEXERLIB_MULTIPLY_LITERAL;
        case TokenType::kDivide: return LEXERLIB_DIVIDE_LITERAL;
        case TokenType::kNumber: return LEXERLIB_NUMBER_LITERAL;
        case TokenType::kIdentifier: return LEXERLIB_IDENTIFIER_LITERAL;
        case TokenType::kSemicolon: return LEXERLIB_SEMICOLON_LITERAL;
        case TokenType::kAssign: return LEXERLIB_ASSIGN_LITERAL;
        case TokenType::kLeftBrac: return LEXERLIB_LEFTBRAC_LITERAL;
        case TokenType::kRightBrac: return LEXERLIB_RIGHTBRAC_LITERAL;
        
        default: return LEXERLIB_ILLEGAL_LITERAL;
    }
}

bool lexerlib::
Token::is_operator()
{
    switch(this->type)
    {
        case TokenType::kPlus: return true;
        case TokenType::kMinus: return true;
        case TokenType::kMultiply: return true;
        case TokenType::kDivide: return true;
        case TokenType::kLeftBrac: return true;
        case TokenType::kRightBrac: return true;
        case TokenType::kAssign: return true;
    }

    return false;
}

void lexerlib::Token::
print()
{
    std::cout << "Type: " << std::setw(LEXERLIB_PRINT_FORMAT_WIDTH) // Left justification
            << std::left << type_to_string(this->get_type()) 
                << " Literal: " << std::setw(LEXERLIB_PRINT_FORMAT_WIDTH) 
                << std::left << this->get_literal();

    this->get_pos().print();
}



bool lexerlib::
Token::is_number()
{
    switch(this->type)
    {
        case TokenType::kNumber: return true;
    }

    return false;
}





lexerlib::TokenType lexerlib::Token::
get_type()
{
    return this->type;
}

std::string lexerlib::Token::
get_literal()
{
    return this->literal;
}

lexerlib::FilePos lexerlib::Token::
get_pos()
{
    return this->pos;
}


lexerlib::TokenType lexerlib::
char_to_token_type(char c)
{
    switch(c)
    {
        case '+': return TokenType::kPlus;
        case '-': return TokenType::kMinus;
        case '*': return TokenType::kMultiply;
        case '/': return TokenType::kDivide;
        case '=': return TokenType::kAssign;
        case ';': return TokenType::kSemicolon;
        case '(': return TokenType::kLeftBrac;
        case ')': return TokenType::kRightBrac;
    }

    if (isdigit(c)) return TokenType::kNumber;
    if (isalnum(c)) return TokenType::kIdentifier;

    return TokenType::kIllegal;
}

bool lexerlib::
is_whitespace(char c)
{
    return (c == ' ' || c == '\n' || c == '\t');
}

lexerlib::FilePos::FilePos()
{
    this->line = 1;
    this->col = 1;
}


void lexerlib::
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

void lexerlib::
FilePos::print()
{
    std::cout << "Line " << this->line << " Col " << this->col << std::endl;
}


std::string::const_iterator lexerlib::
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

    bool has_decimal = false;

    // Continue until token type != start type

    if (start_type == TokenType::kNumber)
    {
        while (it < it_end && ((char_to_token_type(*it) == start_type) 
            || (!has_decimal && *it == '.')))
        {
            if (*it == '.')
            {
                has_decimal = true;
            }

            pos.update_file_pos(*it);
            it++;
        }
    }
    else if (start_type == TokenType::kIdentifier)
    {
        while (it < it_end && ((char_to_token_type(*it) == start_type)))
        {
            pos.update_file_pos(*it);
            it++;
        }
    }
    // else is operator

    token_buf = Token(start_type, std::string(it_start, it), starting_pos);

    // return new position of next token to scan
    return it;
}

lexerlib::Token::Token(){}

lexerlib::Token::~Token(){}

lexerlib::Token::Token(TokenType type, std::string literal, FilePos pos)
{
    this->type = type;
    this->literal = literal;
    this->pos = pos;
}


