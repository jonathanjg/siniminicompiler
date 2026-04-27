#include "evaluator.h"

#include <iostream>
#include <string>

#include "token.h"

void printAst(const Expr* expr, int indent) {
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

    if (const auto* variable = dynamic_cast<const VariableExpr*>(expr)) {
        std::cout << spaces << "VariableExpr(" << variable->name << ")" << std::endl;
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