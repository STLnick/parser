//
// Created by Nick Ray on 3/27/21.
//
#include <iostream>
#include "scanner.hpp"
#include "parser.hpp"
#include "TokenRecord.hpp"

void parser(Scanner *scanner) {
    int lineCount = 1;
    TokenRecord *token = getNextToken(scanner, lineCount);

    program_nt(scanner, token, lineCount); // Grandpappy non-terminal processing

    // TODO: Make the _nt functions advance scanner so when program_nt returns the lookahead is EOF_tk
    // if (token->tokenId != EOF_tk) exit(1);

    return;
}

/*  <program> -> <vars> main <block>  */
void program_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    std::cout << "program_nt() : <vars>" << std::endl; // TODO: _nt function
    vars_nt(scanner, token, lineCount);

    if (token->tokenId == MAIN_tk) {
        token = getNextToken(scanner, lineCount);
        std::cout << "program_nt() : main " << std::endl;
    } else {
        exit(1); // TODO: Improve Error handling
    }

    std::cout << "program_nt() : <block>" << std::endl; // TODO: _nt function
    block_nt(scanner, token, lineCount);
}

/*  <block> -> begin <vars> <stats> end  */
void block_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    if (token->tokenId == BEGIN_tk) { // [Predict] begin <vars> <stats> end
        token = getNextToken(scanner, lineCount);
        std::cout << "block_nt() : begin" << std::endl;

        vars_nt(scanner, token, lineCount);

        stats_nt(scanner, token, lineCount);

        if (token->tokenId == END_tk) {
            token = getNextToken(scanner, lineCount);
            std::cout << "block_nt() : begin" << std::endl;
        } else { // ERROR expected END_tk got ${}
            exit(1); // TODO: Improve error handling
        }

    } else { // ERROR expected BEGIN_tk got ${}
        exit (1); // TODO: Improve error handling
    }
}

/*  <vars> -> ε | data Identifier := Integer ; <vars>  */
void vars_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    if (token->tokenId == DATA_tk) { // [Predict] data Identifier := Integer ; <vars>
        token = getNextToken(scanner, lineCount); // consume DATA_tk token

        if (token->tokenId == ID_tk) token = getNextToken(scanner, lineCount); // Identifier
        else exit(1); // ERROR expected ID_tk got ${}

        if (token->tokenId == COLONEQ_tk) token = getNextToken(scanner, lineCount); // :=
        else exit(1); // ERROR expected COLONEQ_tk got ${}

        if (token->tokenId == NUM_tk) token = getNextToken(scanner, lineCount); // Number
        else exit(1); // ERROR expected NUM_tk got ${}

        if (token->tokenId == SEMI_tk) token = getNextToken(scanner, lineCount); // Semicolon
        else exit(1); // ERROR expected SEMI_tk got ${}

        vars_nt(scanner, token, lineCount); // vars_nt()
    } else { // [Predict] ε
        return;
    }
}

/*  <expr> -> <N> - <expr> | <N>  */
void expr_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <N> -> <A> / <N> | <A> * <N> | <A>  */
void N_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <A> -> <M> + <A> | <M>  */
void A_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <M> -> * <M> | <R>  */
void M_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <R> -> ( <expr> ) | Identifier | Integer  */
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
/*  <stats> -> <stat> <mStat>  */
void stats_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
/*  <mStat> -> ε | <stat> <mStat>  */
void mStat_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
/*  <stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ; |  */
void stat_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
/*  <in> -> getter Identifier  */
void in_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <out> -> outter <expr>  */
void out_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <if> -> if [ <expr> <RO> <expr> ] then <stat> */
void if_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <loop> -> loop [ <expr> <RO> <expr> ] then <stat>  */
void loop_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <assign> -> assign Identifier := <expr>  */
void assign_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <RO> -> => | =< | == | [ == ] (three tokens) | %  */
void RO_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <label> -> void Identifier  */
void label_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <goto> -> proc Identifier  */
void goto_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
