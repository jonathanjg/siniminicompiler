#pragma once

#include <memory>

#include "token.h"

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