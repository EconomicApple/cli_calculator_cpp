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
        case TokenType::kPlus: return PLUS;
        case TokenType::kMinus: return MINUS;
        case TokenType::kMultiply: return MULTIPLY;
        case TokenType::kDivide: return DIVIDE;
        case TokenType::kNumber: return NUMBER;
        case TokenType::kIdentifier: return IDENTIFIER;
        case TokenType::kSemicolon: return SEMICOLON;
        case TokenType::kAssign: return ASSIGN;
        case TokenType::kLeftBrac: return LEFTBRAC;
        case TokenType::kRightBrac: return RIGHTBRAC;
        
        default: return ILLEGAL;
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
    }

    return false;
}

void lexerlib::Token::
print()
{
    std::cout << "Type: " << std::setw(FORMAT_WIDTH) // Left justification
            << std::left << type_to_string(this->get_type()) 
                << " Literal: " << std::setw(FORMAT_WIDTH) 
                << std::left << this->get_literal();

    this->get_pos().print();
}


int lexerlib::
op_precedence(TokenType type)
{
    switch(type)
    {
        case TokenType::kLeftBrac: return LEFTBRAC_PREC;
        case TokenType::kRightBrac: return RIGHTBRAC_PREC;
        case TokenType::kMultiply: return MULTIPLY_PREC;
        case TokenType::kDivide: return DIVIDE_PREC;
        case TokenType::kPlus: return PLUS_PREC;
        case TokenType::kMinus: return MINUS_PREC;

        default: return NOT_OP;
    }
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

double 
lexerlib::operator *(Token t1, Token t2)
{
    if (!(t1.is_number() && t2.is_number()))
    {
        throw_illegal_token();
    }

    return std::stoi(t1.get_literal()) * std::stoi(t2.get_literal());
}

lexerlib::Token::Token(){}

lexerlib::Token::~Token(){}

lexerlib::Token::Token(TokenType type, std::string literal, FilePos pos)
{
    this->type = type;
    this->literal = literal;
    this->pos = pos;
}


