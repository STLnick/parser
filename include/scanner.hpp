//
// Created by Nick Ray on 2/21/21.
//

#ifndef SCANNER_SCANNER_HPP
#define SCANNER_SCANNER_HPP

#include "ScannerStruct.hpp"
#include "TokenRecord.hpp"

void advanceScanner(Scanner *scanner);

Scanner *initScanner(std::string &src);

char lookahead(Scanner *scanner, int offset = 1);

TokenRecord *scannerParseId(Scanner *scanner);

TokenRecord *scannerParseNumber(Scanner *scanner);

TokenRecord *getNextToken(Scanner *scanner, int &lineCnt);

#endif //SCANNER_SCANNER_HPP
