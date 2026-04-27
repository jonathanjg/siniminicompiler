#include "parser.h"

#include <iostream>

#include "evaluator.h"

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