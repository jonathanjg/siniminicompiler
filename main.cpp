#include <iostream>
#include <string>
#include <vector>
#include <cctype>

enum class TokenType {
    Word,
    Number,
    Plus,
    Minus,
    Star,
    Slash,
    Equal,
    Semicolon,
    End
};

struct Token {
    TokenType type;
    std::string text;
};

std::string tokenTypeToString(TokenType type) {
    switch (type) {
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
        case TokenType::End:
            return "END";
    }

    return "UNKNOWN";
}

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

            tokens.push_back({TokenType::Word, word});
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

        std::cout << "Unknown character: " << c << std::endl;
        i++;
    }

    tokens.push_back({TokenType::End, ""});
    return tokens;
}

int main() {
    std::string source = "let x = 10 + 2 * 3 / 4 - 1;";

    std::vector<Token> tokens = lex(source);

    for (const Token& token : tokens) {
        std::cout << tokenTypeToString(token.type);

        if (!token.text.empty()) {
            std::cout << " (" << token.text << ")";
        }

        std::cout << std::endl;
    }

    return 0;
}