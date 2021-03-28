//
// Created by Nick Ray on 3/27/21.
//
#include <iostream>
#include "scanner.hpp"
#include "TokenRecord.hpp"

void program_nt(Scanner *scanner, int &lineCount) {
    std::cout << "program_nt() : <vars>" << std::endl; // TODO: _nt function
    std::cout << "program_nt() : main " << std::endl;
    std::cout << "program_nt() : <block>" << std::endl; // TODO: _nt function
}

void parser(Scanner *scanner) {
    int lineCount = 1;
    TokenRecord *token = getNextToken(scanner, lineCount);

    program_nt(scanner, lineCount); // Grandpappy non-terminal processing

    // TODO: Make the _nt functions advance scanner so when program_nt returns the lookahead is EOF_tk
    // if (token->tokenId != EOF_tk) exit(1);

    return;
}
