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

    if (token->tokenId == MAIN_tk) {
        token = getNextToken(scanner, lineCount);
    } else {
        printErrorAndExit("main", token->tokenId, token->lineNum);
    }

    block_nt(scanner, token, lineCount);

    return; // explicit return
}

/*  <block> -> begin <vars> <stats> end  */
/*  first( <block> ) : { begin }  */
void block_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    if (token->tokenId == BEGIN_tk) { // [Predict] begin <vars> <stats> end
        token = getNextToken(scanner, lineCount);

        vars_nt(scanner, token, lineCount);
        stats_nt(scanner, token, lineCount);

        if (token->tokenId == END_tk) {
            token = getNextToken(scanner, lineCount);
        } else {
            printErrorAndExit("end", token->tokenId, token->lineNum);
        }

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

        if (token->tokenId == ID_tk) {
            token = getNextToken(scanner, lineCount); // Identifier
        } else {
            printErrorAndExit("Identifier", token->tokenId, token->lineNum);
        }

        if (token->tokenId == COLONEQ_tk) {
            token = getNextToken(scanner, lineCount); // :=
        } else {
            printErrorAndExit(":=", token->tokenId, token->lineNum);
        }

        if (token->tokenId == NUM_tk) {
            token = getNextToken(scanner, lineCount); // Number
        } else {
            printErrorAndExit("Number", token->tokenId, token->lineNum);
        }

        if (token->tokenId == SEMI_tk) {
            token = getNextToken(scanner, lineCount); // Semicolon
        } else {
            printErrorAndExit(";", token->tokenId, token->lineNum);
        }

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
    // TODO
}

/*  <N> -> <A> / <N> | <A> * <N> | <A>  */
/*  first( <N> ) : { first(A) }  */
// process <A> - then check for '/', '*', or nothing to choose production
void N_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
}

/*  <A> -> <M> + <A> | <M>  */
/*  first( <A> ) : { '* <M>': *, '<R>': [ '(', Identifier, Integer/Number ] }  */
// process <M> if PLUS_tk process <M> + <A> else just process <M> and return
void A_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
}

/*  <M> -> * <M> | <R>  */
/*  first( <M> ) : { '* <M>': *, '<R>': [ '(', Identifier, Integer/Number ] }  */
void M_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
}

/*  <R> -> ( <expr> ) | Identifier | Integer  */
/*  first( <R> ) : { '( <expr> )': '(', 'Identifier': Identifier, 'Integer': Integer/Number }  */
void R_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
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
        if (token->tokenId == SEMI_tk) {
            token = getNextToken(scanner, lineCount);
        } else {
            printErrorAndExit(";", token->tokenId, token->lineNum);
        }
    } else if (token->tokenId == OUTTER_tk) {
        out_nt(scanner, token, lineCount);
        if (token->tokenId == SEMI_tk) {
            token = getNextToken(scanner, lineCount);
        } else {
            printErrorAndExit("outter", token->tokenId, token->lineNum);
        }
    } else if (token->tokenId == BEGIN_tk) {
        block_nt(scanner, token, lineCount);
    } else if (token->tokenId == IF_tk) {
        if_nt(scanner, token, lineCount);
        if (token->tokenId == SEMI_tk) {
            token = getNextToken(scanner, lineCount);
        } else {
            printErrorAndExit("begin", token->tokenId, token->lineNum);
        }
    } else if (token->tokenId == LOOP_tk) {
        loop_nt(scanner, token, lineCount);
        if (token->tokenId == SEMI_tk) {
            token = getNextToken(scanner, lineCount);
        } else {
            printErrorAndExit("loop", token->tokenId, token->lineNum);
        }
    } else if (token->tokenId == ASSIGN_tk) {
        assign_nt(scanner, token, lineCount);
        if (token->tokenId == SEMI_tk) {
            token = getNextToken(scanner, lineCount);
        } else {
            printErrorAndExit("assign", token->tokenId, token->lineNum);
        }
    } else if (token->tokenId == PROC_tk) {
        goto_nt(scanner, token, lineCount);
        if (token->tokenId == SEMI_tk) {
            token = getNextToken(scanner, lineCount);
        } else {
            printErrorAndExit("proc", token->tokenId, token->lineNum);
        }
    } else if (token->tokenId == VOID_tk) {
        label_nt(scanner, token, lineCount);
        if (token->tokenId == SEMI_tk) {
            token = getNextToken(scanner, lineCount);
        } else {
            printErrorAndExit("void", token->tokenId, token->lineNum);
        }
    } else {
        printErrorAndExit("getter/outter/begin/if/loop/assign/proc/void", token->tokenId, token->lineNum);
    }

    return; // explicit return
}

/*  <in> -> getter Identifier  */
/*  first( <in> ) : { getter }  */
void in_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    if (token->tokenId == GETTER_tk) {
        token = getNextToken(scanner, lineCount);
    } else {
        printErrorAndExit("getter", token->tokenId, token->lineNum);
    }

    if (token->tokenId == ID_tk) {
        token = getNextToken(scanner, lineCount);
    } else {
        printErrorAndExit("Identifier", token->tokenId, token->lineNum);
    }

    return; // explicit return
}

/*  <out> -> outter <expr>  */
/*  first( <out> ) : { outter }  */
void out_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
    return; // explicit return
}

/*  <if> -> if [ <expr> <RO> <expr> ] then <stat> */
/*  first( <if> ) : { if }  */
void if_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
    return; // explicit return
}

/*  <loop> -> loop [ <expr> <RO> <expr> ] then <stat>  */
/*  first( <loop> ) : { loop }  */
void loop_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
    return; // explicit return
}

/*  <assign> -> assign Identifier := <expr>  */
/*  first( <assign> ) : { assign }  */
void assign_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
    return; // explicit return
}

/*  <RO> -> => | =< | == | [ == ] (three tokens) | %  */
/*  first( <R0> ) : { =, %, [ }  */
void RO_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO: process the first '=' for all two char tokens
    return; // explicit return
}

/*  <label> -> void Identifier  */
/*  first( <label> ) : { void }  */
void label_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
    return; // explicit return
}

/*  <goto> -> proc Identifier  */
/*  first( <goto> ) : { proc }  */
void goto_nt(Scanner *scanner, TokenRecord *&token, int &lineCount) {
    // TODO
    return; // explicit return
}

void checkAndConsumeTerminal(Scanner *scanner, TokenRecord *&token, int &lineCount, tokenID targetId) {
    if (token->tokenId == targetId) {
        token = getNextToken(scanner, lineCount);
    } else {
        printErrorAndExit(tokenNames[targetId], token->tokenId, token->lineNum);
    }
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
