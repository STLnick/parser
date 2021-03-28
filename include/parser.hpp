//
// Created by Nick Ray on 3/27/21.
//

#ifndef PARSER_PARSER_HPP
#define PARSER_PARSER_HPP
#include "scanner.hpp"

void program_nt(Scanner *scanner, int &lineCount);
void parser(Scanner *scanner);

#endif //PARSER_PARSER_HPP
