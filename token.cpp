#include "token.h"

std::string tokenTypeToString(TokenType type) {
    switch (type) {
        case TokenType::Let:
            return "LET";
        case TokenType::Print:
            return "PRINT";
        case TokenType::Word:
            return "WORD";
        case TokenType::Number:
            return "NUMBER";
        case TokenType::Plus:
            return "PLUS";
        case TokenType::Minus:
            return "MINUS";
        case TokenType::Star:
            return "STAR";
        case TokenType::Slash:
            return "SLASH";
        case TokenType::Equal:
            return "EQUAL";
        case TokenType::Semicolon:
            return "SEMICOLON";
        case TokenType::LeftParen:
            return "LEFT_PAREN";
        case TokenType::RightParen:
            return "RIGHT_PAREN";
        case TokenType::End:
            return "END";
    }

    return "UNKNOWN";
}