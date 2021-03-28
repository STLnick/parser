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

    if (token->tokenId != EOF_tk) exit(1);

    return;
}

/*  <program> -> <vars> main <block>  */
/*  first( <program> ) : { data, main }  */
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

    return; // explicit return
}

/*  <block> -> begin <vars> <stats> end  */
/*  first( <block> ) : { begin }  */
void block_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    if (token->tokenId == BEGIN_tk) { // [Predict] begin <vars> <stats> end
        token = getNextToken(scanner, lineCount);
        std::cout << "block_nt() : begin" << std::endl;

        vars_nt(scanner, token, lineCount);

        stats_nt(scanner, token, lineCount);

        if (token->tokenId == END_tk) {
            token = getNextToken(scanner, lineCount);
            std::cout << "block_nt() : end" << std::endl;
        } else { // ERROR expected END_tk got ${}
            exit(1); // TODO: Improve error handling
        }

        return; // explicit return
    } else { // ERROR expected BEGIN_tk got ${}
        exit (1); // TODO: Improve error handling
    }
}

/*  <vars> -> ε | data Identifier := Integer ; <vars>  */
/*  first( <vars> ) : { data }  */
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
        return; // explicit return
    } else { // [Predict] ε
        return;
    }
}

/*  <expr> -> <N> - <expr> | <N>  */
/*  first( <expr> ) : { first(N) }  */
// process <N> - then check for '-' to choose production
void expr_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <N> -> <A> / <N> | <A> * <N> | <A>  */
/*  first( <N> ) : { first(A) }  */
// process <A> - then check for '/', '*', or nothing to choose production
void N_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <A> -> <M> + <A> | <M>  */
/*  first( <A> ) : { '* <M>': *, '<R>': [ '(', Identifier, Integer/Number ] }  */
// process <M> if PLUS_tk process <M> + <A> else just process <M> and return
void A_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <M> -> * <M> | <R>  */
/*  first( <M> ) : { '* <M>': *, '<R>': [ '(', Identifier, Integer/Number ] }  */
void M_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <R> -> ( <expr> ) | Identifier | Integer  */
/*  first( <R> ) : { '( <expr> )': '(', 'Identifier': Identifier, 'Integer': Integer/Number }  */
void R_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/* TODO * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*  <stats> -> <stat> <mStat>  */
/*  first( <stats> ) : { '<stat> <mStat>': [getter, outter, begin, if, loop, assign, proc, void] }  */
void stats_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    stat_nt(scanner, token, lineCount);

    mStat_nt(scanner, token, lineCount);

    return; // explicit return
}

/*  <mStat> -> ε | <stat> <mStat>  */
/*  first( <mStat> ) : { '<stat> <mStat>': [getter, outter, begin, if, loop, assign, proc, void] }  */
void mStat_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    if (token->tokenId == ) {

        return; // explicit return
    } else { // [Predict] ε
        return;
    }
}

/*  <stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ; |  */
/*  first( <stat> ) : { '<in>': getter, '<out>': outter, '<block>': begin, '<if>': if,
 *                      '<loop>': loop, '<assign>': assign, '<goto>': proc, '<label>': void }  */
void stat_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
int isInFirstOfStat(tokenID id) {
    const tokenID statFirsts[] = {
            GETTER_tk,
            OUTTER_tk,
            BEGIN_tk,
            IF_tk,
            LOOP_tk,
            ASSIGN_tk,
            PROC_tk,
            VOID_tk
    };
    int len = sizeof(statFirsts) / sizeof(statFirsts[0]);
    int i;

    for(i = 0; i < len; i++) {
        if (statFirsts[i] == id) return 1;
    }

    return 0;
}

/* TODO * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*  <in> -> getter Identifier  */
/*  first( <in> ) : { getter }  */
void in_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <out> -> outter <expr>  */
/*  first( <out> ) : { outter }  */
void out_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <if> -> if [ <expr> <RO> <expr> ] then <stat> */
/*  first( <if> ) : { if }  */
void if_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <loop> -> loop [ <expr> <RO> <expr> ] then <stat>  */
/*  first( <loop> ) : { loop }  */
void loop_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <assign> -> assign Identifier := <expr>  */
/*  first( <assign> ) : { assign }  */
void assign_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <RO> -> => | =< | == | [ == ] (three tokens) | %  */
/*  first( <R0> ) : { =, %, [ }  */
void RO_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO: process the first '=' for all two char tokens
}

/*  <label> -> void Identifier  */
/*  first( <label> ) : { void }  */
void label_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}

/*  <goto> -> proc Identifier  */
/*  first( <goto> ) : { proc }  */
void goto_nt(Scanner *scanner, TokenRecord *token, int &lineCount) {
    // TODO
}
