#pragma once

#include "ast.h"

void printAst(const Expr* expr, int indent = 0);
int evaluateAst(const Expr* expr);