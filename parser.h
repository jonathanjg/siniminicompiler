#pragma once

#include <memory>
#include <vector>

#include "ast.h"
#include "token.h"

std::unique_ptr<Expr> parseExpressionAst(const std::vector<Token>& tokens, int& i);
void runPrintStatement(const std::vector<Token>& tokens);