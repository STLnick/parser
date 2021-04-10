//
// Created by Nick Ray on 3/27/21.
//

#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP
#include "scanner.hpp"

node* parser(Scanner *scanner);
node* program_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* block_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* vars_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* expr_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* N_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* A_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* M_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* R_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* stats_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* mStat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* stat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* in_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* out_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* if_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* loop_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* assign_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* RO_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* label_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
node* goto_nt(Scanner *scanner, TokenRecord *&token, int &lineCount);
void checkAndConsumeTerminal(Scanner *scanner, TokenRecord *&token, int &lineCount, tokenID targetId, node* treeNode);
int isInFirstOfR(tokenID id);
int isInFirstOfStat(tokenID id);
void printErrorAndExit(std::string expected, tokenID received, int line);

#endif //PARSER_PARSER_HPP
