#include "lexer.h"

#include <cctype>
#include <iostream>

std::vector<Token> lex(const std::string& source) {
    std::vector<Token> tokens;

    int i = 0;

    while (i < source.length()) {
        char c = source[i];

        if (std::isspace(c)) {
            i++;
            continue;
        }

        if (std::isalpha(c)) {
            std::string word;

            while (i < source.length() && std::isalpha(source[i])) {
                word += source[i];
                i++;
            }

            if (word == "let") {
                tokens.push_back({TokenType::Let, word});
            } else if (word == "print") {
                tokens.push_back({TokenType::Print, word});
            } else {
                tokens.push_back({TokenType::Word, word});
            }

            continue;
        }

        if (std::isdigit(c)) {
            std::string number;

            while (i < source.length() && std::isdigit(source[i])) {
                number += source[i];
                i++;
            }

            tokens.push_back({TokenType::Number, number});
            continue;
        }

        if (c == '+') {
            tokens.push_back({TokenType::Plus, "+"});
            i++;
            continue;
        }

        if (c == '-') {
            tokens.push_back({TokenType::Minus, "-"});
            i++;
            continue;
        }

        if (c == '*') {
            tokens.push_back({TokenType::Star, "*"});
            i++;
            continue;
        }

        if (c == '/') {
            tokens.push_back({TokenType::Slash, "/"});
            i++;
            continue;
        }

        if (c == '=') {
            tokens.push_back({TokenType::Equal, "="});
            i++;
            continue;
        }

        if (c == ';') {
            tokens.push_back({TokenType::Semicolon, ";"});
            i++;
            continue;
        }

        if (c == '(') {
            tokens.push_back({TokenType::LeftParen, "("});
            i++;
            continue;
        }

        if (c == ')') {
            tokens.push_back({TokenType::RightParen, ")"});
            i++;
            continue;
        }

        std::cout << "Unknown character: " << c << std::endl;
        i++;
    }

    tokens.push_back({TokenType::End, ""});
    return tokens;
}