//
// Created by Nick Ray on 3/27/21.
//
#include <iostream>
#include "scanner.hpp"
#include "TokenRecord.hpp"

void S() {
    std::cout << "S()" << std::endl;
}

void parser(Scanner *scanner) {
    int lineCount = 1;
    TokenRecord *token = getNextToken(scanner, lineCount);

    S(); // Grandpappy non-terminal processing

    if (token->tokenId != EOF_tk) exit(1);

    return;
}
