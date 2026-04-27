#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <memory>

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

struct Expr {
    virtual ~Expr() = default;
};

struct NumberExpr : Expr {
    int value;

    explicit NumberExpr(int value)
        : value(value) {}
};

struct BinaryExpr : Expr {
    TokenType op;
    std::unique_ptr<Expr> left;
    std::unique_ptr<Expr> right;

    BinaryExpr(TokenType op, std::unique_ptr<Expr> left, std::unique_ptr<Expr> right)
        : op(op), left(std::move(left)), right(std::move(right)) {}
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
        case TokenType::LeftParen:
            return "LEFT_PAREN";
        case TokenType::RightParen:
            return "RIGHT_PAREN";
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

// Helper Functions
bool isExpressionOperator(TokenType type) {
    return type == TokenType::Plus || type == TokenType::Minus;
}

bool isTermOperator(TokenType type) {
    return type == TokenType::Star || type == TokenType::Slash;
}









std::unique_ptr<Expr> parseExpressionAst(const std::vector<Token>& tokens, int& i);

std::unique_ptr<Expr> parseFactorAst(const std::vector<Token>& tokens, int& i) {
    if (tokens[i].type == TokenType::Number) {
        int value = std::stoi(tokens[i].text);
        i++;
        return std::make_unique<NumberExpr>(value);
    }

    if (tokens[i].type == TokenType::LeftParen) {
        i++;

        std::unique_ptr<Expr> expr = parseExpressionAst(tokens, i);

        if (tokens[i].type != TokenType::RightParen) {
            std::cout << "Error: expected ')' after expression" << std::endl;
            return nullptr;
        }

        i++;
        return expr;
    }

    std::cout << "Error: expected number or '('" << std::endl;
    return nullptr;
}

std::unique_ptr<Expr> parseTermAst(const std::vector<Token>& tokens, int& i) {
    std::unique_ptr<Expr> left = parseFactorAst(tokens, i);

    if (!left) {
        return nullptr;
    }

    while (isTermOperator(tokens[i].type)) {
        TokenType op = tokens[i].type;
        i++;

        std::unique_ptr<Expr> right = parseFactorAst(tokens, i);

        if (!right) {
            return nullptr;
        }

        left = std::make_unique<BinaryExpr>(
            op,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}

std::unique_ptr<Expr> parseExpressionAst(const std::vector<Token>& tokens, int& i) {
    std::unique_ptr<Expr> left = parseTermAst(tokens, i);

    if (!left) {
        return nullptr;
    }

    while (isExpressionOperator(tokens[i].type)) {
        TokenType op = tokens[i].type;
        i++;

        std::unique_ptr<Expr> right = parseTermAst(tokens, i);

        if (!right) {
            return nullptr;
        }

        left = std::make_unique<BinaryExpr>(
            op,
            std::move(left),
            std::move(right)
        );
    }

    return left;
}

void printAst(const Expr* expr, int indent = 0) {
    std::string spaces(indent, ' ');

    if (const auto* number = dynamic_cast<const NumberExpr*>(expr)) {
        std::cout << spaces << "NumberExpr(" << number->value << ")" << std::endl;
        return;
    }

    if (const auto* binary = dynamic_cast<const BinaryExpr*>(expr)) {
        std::cout << spaces << "BinaryExpr(" << tokenTypeToString(binary->op) << ")" << std::endl;

        printAst(binary->left.get(), indent + 2);
        printAst(binary->right.get(), indent + 2);
        return;
    }

    std::cout << spaces << "Unknown Expr" << std::endl;
}

int evaluateAst(const Expr* expr) {
    if (const auto* number = dynamic_cast<const NumberExpr*>(expr)) {
        return number->value;
    }

    if (const auto* binary = dynamic_cast<const BinaryExpr*>(expr)) {
        int left = evaluateAst(binary->left.get());
        int right = evaluateAst(binary->right.get());

        if (binary->op == TokenType::Plus) {
            return left + right;
        }

        if (binary->op == TokenType::Minus) {
            return left - right;
        }

        if (binary->op == TokenType::Star) {
            return left * right;
        }

        if (binary->op == TokenType::Slash) {
            if (right == 0) {
                std::cout << "Error: division by zero" << std::endl;
                return 0;
            }

            return left / right;
        }
    }

    std::cout << "Error: unknown AST node" << std::endl;
    return 0;
}

void runPrintStatement(const std::vector<Token>& tokens) {
    int i = 0;

    if (tokens[i].type != TokenType::Print) {
        std::cout << "Error: expected 'print'" << std::endl;
        return;
    }
    i++;

    std::unique_ptr<Expr> ast = parseExpressionAst(tokens, i);

    if (!ast) {
        return;
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

    std::cout << "=== AST ===" << std::endl;
    printAst(ast.get());

    std::cout << std::endl;
    std::cout << "=== AST EVALUATOR ===" << std::endl;
    std::cout << "AST Result: " << evaluateAst(ast.get()) << std::endl;
}

int main() {
    std::string source = "print (10 - 2) * 3 + 1 + 2;";

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

    runPrintStatement(tokens);

    return 0;
}