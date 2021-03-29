//
// Created by Nick Ray on 3/27/21.
//

#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP
#include "scanner.hpp"

void parser(Scanner *scanner);
void program_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void block_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void vars_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void expr_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void N_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void A_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void M_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void R_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void stats_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void mStat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void stat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void in_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void out_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void if_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void loop_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void assign_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void RO_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void label_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void goto_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void checkAndConsumeTerminal(Scanner *scanner, TokenRecord *&token, int &lineCount, tokenID targetId);
int isInFirstOfStat(tokenID id);
void printErrorAndExit(std::string expected, tokenID received, int line);

#endif //PARSER_PARSER_HPP
