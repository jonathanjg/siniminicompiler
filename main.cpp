#include <iostream>
#include <string>
#include <vector>

#include "lexer.h"
#include "parser.h"
#include "token.h"

int main() {
    std::string source = "print (10 - 1) * 3 + 1 + 2;";

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