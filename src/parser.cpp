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
void expr_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void N_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void A_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void M_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void R_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void stats_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void mStat_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void stat_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void in_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void out_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void if_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void loop_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void assign_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void RO_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void label_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
void goto_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
