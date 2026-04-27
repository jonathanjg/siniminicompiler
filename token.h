#pragma once

#include <string>

enum class TokenType {
    Let,
    Print,
    Word,
    Number,
    Plus,
    Minus,
    Star,
    Slash,
    Equal,
    Semicolon,
    LeftParen,
    RightParen,
    End
};

struct Token {
    TokenType type;
    std::string text;
};

std::string tokenTypeToString(TokenType type);