#include <iostream>
#include <string>
#include <vector>
#include <cctype>

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
    End
};

struct Token {
    TokenType type;
    std::string text;
};

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

        std::cout << "Unknown character: " << c << std::endl;
        i++;
    }

    tokens.push_back({TokenType::End, ""});
    return tokens;
}

// Helper Functions
bool isValue(TokenType type) {
    return type == TokenType::Number || type == TokenType::Word;
}
bool isOperator(TokenType type) {
    return type == TokenType::Plus || type == TokenType::Minus || type == TokenType::Star || type == TokenType::Slash;
}

void parsePrintStatement(const std::vector<Token>& tokens) {
    int i = 0;

    // // second debug loop
    // for (const auto& t : tokens) {
    //     std::cout << tokenTypeToString(t.type) << ": " << t.text << "\n";
    // }

    if (tokens[i].type != TokenType::Print) {
        std::cout << "Error: expected 'print'" << std::endl;
        return;
    }
    i++;

    if (!isValue(tokens[i].type)) {
        std::cout << "Error: expected number or variable after 'print'" << std::endl;
        return;
    }
    i++;

    while (isOperator(tokens[i].type)) {
        i++;

        if (!isValue(tokens[i].type)) {
            std::cout << "Error: expected number or variable after operator" << std::endl;
            return;
        }

        i++;
    }

    if (tokens[i].type != TokenType::Semicolon) {
        std::cout << "Error: expected ';' after expression" << std::endl;
        return;
    }
    i++;

    if (tokens[i].type != TokenType::End) {
        std::cout << "Error: unexpected tokens after statement" << std::endl;
        return;
    }

    std::cout << "Valid print statement!" << std::endl;
}

int main() {
    std::string source = "print x +2;";

    std::vector<Token> tokens = lex(source);

    std::cout << "=== TOKENS ===" << std::endl;

    for (const Token& token : tokens) {
        std::cout << tokenTypeToString(token.type);

        if (!token.text.empty()) {
            std::cout << " (" << token.text << ")";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "=== PARSER ===" << std::endl;

    parsePrintStatement(tokens);

    return 0;
}