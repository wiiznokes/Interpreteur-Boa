#ifndef SYNTAX_ANALYSE_H
#define SYNTAX_ANALYSE_H

#include <stdbool.h>


#include "tree.h"





void fill_ast(char *fileName, bool show_log);


void stop_analyse();



/*
    *** grammaire ***

    instructions: instuction instructions
    instructions:

    instruction: initialisation ;
    instruction: assignation ;
    instruction: fonction
    instruction: condition
    instruction: return ;

    return: RETURN
    return: RETURN eag


    initialisation: type name <- eag
    assignation: name = eag



    eag: seq_terme
    seq_terme: terme suite_seq_terme
    suite_seq_terme: op1 terme suite_seq_terme
    suite_seq_terme:
    terme: seq_facteur
    seq_facteur: facteur suite_seq_facteur
    suite_seq_facteur: op2 facteur suite_seq_facteur
    suite_seq_facteur:
    facteur: VARIABLE
    facteur: call
    facteur: INTEGER
    facteur: CHAR
    facteur: PARO eag PARF
    facteur: MOINS facteur
    facteur: NOT facteur
    op1: PLUS MOINS
    op2: MUL DIV OR AND EQUAL NOT_EQUAL LESS MORE LESS_EQUAL MORE_EQUAL

    

    


    fonction: fun name ( args ) : type { instructions }

    args: arg arg_suite
    args:

    arg: type name

    arg_suite: , arg
    arg_suite:



    call: NAME ( call_args )
    call_args:
    call_args: eag suite_call_args
    suite_call_args:
    suite_call_args: , suite_call_args



    




    condition: if_block else_block
    condition: if_block


    if_block: if ( eag ) { instructions }
    else_block: else { instructions }






    while_loop: while ( operations ) { instructions }


*/

#endif
