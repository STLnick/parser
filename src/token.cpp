#include <iostream>
#include <stdlib.h>
#include <string>
#include "TokenRecord.hpp"

TokenRecord *initToken(std::string name, tokenID tokenId, int lineNum) {
    std::cout << "initToken -- -- --" << std::endl;
    TokenRecord *newToken;
    std::cout << "initToken 2 -- -- --" << std::endl;
    newToken = (TokenRecord *) malloc(1 * sizeof(TokenRecord));
    std::cout << "initToken 3 : malloced -- -- --" << std::endl;
    std::cout << "initToken 3a : name - " << name << std::endl;
    newToken->stringVal = name;
    std::cout << "initToken 4 : assigned name to stringVal -- -- --" << std::endl;
    newToken->tokenId = tokenId;
    std::cout << "initToken 5 : assigned " << tokenId << " to tokenId-- -- --" << std::endl;
    newToken->lineNum = lineNum;
    std::cout << "initToken 6 : assigned " << lineNum << " to lineNum-- -- --" << std::endl;
    return newToken;
}

void printToken(TokenRecord *token) {
    std::cout << "[" << tokenNames[token->tokenId] << "] '" << token->stringVal << "' on line " << token->lineNum << std::endl;
}