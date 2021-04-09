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

    if (token->tokenId != EOF_tk) {
        printErrorAndExit("End of File", token->tokenId, token->lineNum);
    }

    return;
}

/*  <program> -> <vars> main <block>  */
/*  first( <program> ) : { data, main }  */
void program_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    vars_nt(scanner, token, lineCount);

    checkAndConsumeTerminal(scanner, token, lineCount, MAIN_tk);

    block_nt(scanner, token, lineCount);

    return; // explicit return
}

/*  <block> -> begin <vars> <stats> end  */
/*  first( <block> ) : { begin }  */
void block_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    if (token->tokenId == BEGIN_tk) { // [Predict] begin <vars> <stats> end
        token = getNextToken(scanner, lineCount); // consume BEGIN_tk

        vars_nt(scanner, token, lineCount);
        stats_nt(scanner, token, lineCount);

        checkAndConsumeTerminal(scanner, token, lineCount, END_tk);

        return; // explicit return
    } else {
        printErrorAndExit("begin", token->tokenId, token->lineNum);
    }
}

/*  <vars> -> ε | data Identifier := Integer ; <vars>  */
/*  first( <vars> ) : { data }  */
void vars_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    if (token->tokenId == DATA_tk) { // [Predict] data Identifier := Integer ; <vars>
        token = getNextToken(scanner, lineCount); // consume DATA_tk token

        checkAndConsumeTerminal(scanner, token, lineCount, ID_tk);

        checkAndConsumeTerminal(scanner, token, lineCount, COLONEQ_tk);

        checkAndConsumeTerminal(scanner, token, lineCount, NUM_tk);

        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk);

        vars_nt(scanner, token, lineCount); // vars_nt()

        return; // explicit return
    } else { // [Predict] ε
        return;
    }
}

/*  <expr> -> <N> - <expr> | <N>  */
/*  first( <expr> ) : { first(N) }  */
// process <N> - then check for '-' to choose production
void expr_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: TEST ME!!!
    N_nt(scanner, token, lineCount);

    if (token->tokenId == MINUS_tk) { // [Predict] <N> - <expr>
        checkAndConsumeTerminal(scanner, token, lineCount, MINUS_tk);
        expr_nt(scanner, token, lineCount);
    }

    return; // explicit return
}

/*  <N> -> <A> / <N> | <A> * <N> | <A>  */
/*  first( <N> ) : { first(A) }  */
// process <A> - then check for '/', '*', or nothing to choose production
void N_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: TEST ME!!!
    A_nt(scanner, token, lineCount);

    if (token->tokenId == DIVIDE_tk) { // [Predict] <A> / <N>
        checkAndConsumeTerminal(scanner, token, lineCount, DIVIDE_tk);
        N_nt(scanner, token, lineCount);
    } else if (token->tokenId == MULT_tk) { // [Predict] <A> * <N>
        checkAndConsumeTerminal(scanner, token, lineCount, MULT_tk);
        N_nt(scanner, token, lineCount);
    }

    return; // explicit return
}

/*  <A> -> <M> + <A> | <M>  */
/*  first( <A> ) : { '* <M>': *, '<R>': [ '(', Identifier, Integer/Number ] }  */
// process <M> if PLUS_tk process <M> + <A> else just process <M> and return
void A_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: TEST ME!!!
    M_nt(scanner, token, lineCount);

    if (token->tokenId == PLUS_tk) { // [Predict] <M> + <A>
        checkAndConsumeTerminal(scanner, token, lineCount, PLUS_tk);
        A_nt(scanner, token, lineCount);
    }

    return; // explicit return
}

/*  <M> -> * <M> | <R>  */
/*  first( <M> ) : { '* <M>': *, '<R>': [ '(', Identifier, Integer/Number ] }  */
void M_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    if (token->tokenId == MULT_tk) { // [Predict] * <M>
        checkAndConsumeTerminal(scanner, token, lineCount, MULT_tk);
        M_nt(scanner, token, lineCount);
    } else if ( isInFirstOfR(token->tokenId) ) {
        R_nt(scanner, token, lineCount);
    } else {
        printErrorAndExit("* / Left Parenthesis / Identifier / Integer", token->tokenId, token->lineNum);
    }

    return; // explicit return
}

/*  <R> -> ( <expr> ) | Identifier | Integer  */
/*  first( <R> ) : { '( <expr> )': '(', 'Identifier': Identifier, 'Integer': Integer/Number }  */
void R_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: TEST ME!!!
    if (token->tokenId == LPAREN_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, LPAREN_tk);
        expr_nt(scanner, token, lineCount);
        checkAndConsumeTerminal(scanner, token, lineCount, RPAREN_tk);
    } else if (token->tokenId == ID_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, ID_tk);
    } else if (token->tokenId == NUM_tk) {
        checkAndConsumeTerminal(scanner, token, lineCount, NUM_tk);
    } else {
        printErrorAndExit("Left Parenthesis / Identifier / Integer", token->tokenId, token->lineNum);
    }

    return; // explicit return
}

/*  <stats> -> <stat> <mStat>  */
/*  first( <stats> ) : { '<stat> <mStat>': [getter, outter, begin, if, loop, assign, proc, void] }  */
void stats_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    stat_nt(scanner, token, lineCount);
    mStat_nt(scanner, token, lineCount);
    return; // explicit return
}

/*  <mStat> -> ε | <stat> <mStat>  */
/*  first( <mStat> ) : { '<stat> <mStat>': [getter, outter, begin, if, loop, assign, proc, void] }  */
void mStat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    if ( isInFirstOfStat(token->tokenId) ) { // [Predict] <stat> <mStat>
        stat_nt(scanner, token, lineCount);
        mStat_nt(scanner, token, lineCount);
        return; // explicit return
    } else { // [Predict] ε
        return; // explicit return
    }
}

/*  <stat> -> <in> ; | <out> ; | <block> | <if> ; | <loop> ; | <assign> ; | <goto> ; | <label> ; |  */
/*  first( <stat> ) : { '<in>': getter, '<out>': outter, '<block>': begin, '<if>': if,
 *                      '<loop>': loop, '<assign>': assign, '<goto>': proc, '<label>': void }  */
void stat_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    if (token->tokenId == GETTER_tk) {
        in_nt(scanner, token, lineCount);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk);
    } else if (token->tokenId == OUTTER_tk) {
        out_nt(scanner, token, lineCount);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk);
    } else if (token->tokenId == BEGIN_tk) {
        block_nt(scanner, token, lineCount);
    } else if (token->tokenId == IF_tk) {
        if_nt(scanner, token, lineCount);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk);
    } else if (token->tokenId == LOOP_tk) {
        loop_nt(scanner, token, lineCount);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk);
    } else if (token->tokenId == ASSIGN_tk) {
        assign_nt(scanner, token, lineCount);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk);
    } else if (token->tokenId == PROC_tk) {
        goto_nt(scanner, token, lineCount);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk);
    } else if (token->tokenId == VOID_tk) {
        label_nt(scanner, token, lineCount);
        checkAndConsumeTerminal(scanner, token, lineCount, SEMI_tk);
    } else {
        printErrorAndExit("getter/outter/begin/if/loop/assign/proc/void", token->tokenId, token->lineNum);
    }

    return; // explicit return
}

/*  <in> -> getter Identifier  */
/*  first( <in> ) : { getter }  */
void in_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    checkAndConsumeTerminal(scanner, token, lineCount, GETTER_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, ID_tk);
    return; // explicit return
}

/*  <out> -> outter <expr>  */
/*  first( <out> ) : { outter }  */
void out_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: TEST ME!!!
    checkAndConsumeTerminal(scanner, token, lineCount, OUTTER_tk);
    expr_nt(scanner, token, lineCount);
    return; // explicit return
}

/*  <if> -> if [ <expr> <RO> <expr> ] then <stat> */
/*  first( <if> ) : { if }  */
void if_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: TEST ME!!!
    checkAndConsumeTerminal(scanner, token, lineCount, IF_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, LBRACKET_tk);

    expr_nt(scanner, token, lineCount);
    RO_nt(scanner, token, lineCount);
    expr_nt(scanner, token, lineCount);

    checkAndConsumeTerminal(scanner, token, lineCount, RBRACKET_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, THEN_tk);

    stat_nt(scanner, token, lineCount);

    return; // explicit return
}

/*  <loop> -> loop [ <expr> <RO> <expr> ] then <stat>  */
/*  first( <loop> ) : { loop }  */
void loop_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: TEST ME!!!
    checkAndConsumeTerminal(scanner, token, lineCount, LOOP_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, LBRACKET_tk);

    expr_nt(scanner, token, lineCount);
    RO_nt(scanner, token, lineCount);
    expr_nt(scanner, token, lineCount);

    checkAndConsumeTerminal(scanner, token, lineCount, RBRACKET_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, THEN_tk);

    stat_nt(scanner, token, lineCount);

    return; // explicit return
}

/*  <assign> -> assign Identifier := <expr>  */
/*  first( <assign> ) : { assign }  */
void assign_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    checkAndConsumeTerminal(scanner, token, lineCount, ASSIGN_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, ID_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, COLONEQ_tk);
    expr_nt(scanner, token, lineCount); // TODO
    return; // explicit return
}

/*  <RO> -> => | =< | == | [ == ] (three tokens) | %  */
/*  first( <R0> ) : { =, %, [ }  */
void RO_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: process the first '=' for all two char tokens
    checkAndConsumeTerminal(scanner, token, lineCount, VOID_tk);


    return; // explicit return
}

/*  <label> -> void Identifier  */
/*  first( <label> ) : { void }  */
void label_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    checkAndConsumeTerminal(scanner, token, lineCount, VOID_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, ID_tk);
    return; // explicit return
}

/*  <goto> -> proc Identifier  */
/*  first( <goto> ) : { proc }  */
void goto_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    checkAndConsumeTerminal(scanner, token, lineCount, PROC_tk);
    checkAndConsumeTerminal(scanner, token, lineCount, ID_tk);
    return; // explicit return
}

void checkAndConsumeTerminal(Scanner *scanner, TokenRecord *&token, int &lineCount, tokenID targetId) {
    if (token->tokenId == targetId) {
        token = getNextToken(scanner, lineCount);
    } else {
        printErrorAndExit(tokenNames[targetId], token->tokenId, token->lineNum);
    }
}

int isInFirstOfR(tokenID id) {
    const tokenID rFirsts[] = {
            LPAREN_tk,
            ID_tk,
            NUM_tk
    };
    int len = sizeof(rFirsts) / sizeof(rFirsts[0]);
    int i;

    for(i = 0; i < len; i++) {
        if (rFirsts[i] == id) return 1;
    }

    return 0;
}

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

void printErrorAndExit(std::string expected, tokenID received, int line) {
    std::cout   << "ERROR: Expected '" << expected << "' on line " << line
                << " but received '" << tokenLiterals[received] << "' instead." << std::endl;
    exit(1);
}
