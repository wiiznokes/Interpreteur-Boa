#ifndef SYNTAX_ANALYSE_H
#define SYNTAX_ANALYSE_H

#include "stdbool.h"


#include "tree.h"





void fill_ast(char *fileName);


void stop_analyse();


tree *get_ast();

/*
    Grammaire:

    instructions: instuction instructions
    instructions:

    instruction: initialisation ;
    instruction: assignation ;
    instruction: fonction
    instruction: if_statement
    instruction: while_loop


    initialisation: type name <- operations
    assignation: name = operations

    operation: name
    operation: valeur

    operations: operation operations_rec

    operations_rec: operation operations_rec
    operations_rec:

    fonction: fun name ( args ) : type { instructions }

    args: operations_rec

    if_statement: if_block else_block
    if_statement: if_block


    if_block: if ( operations ) { instructions }
    else_block: else { instructions }

    while_loop: while ( operations ) { instructions }





    grammaire calculette

    eag → seq terme
    seq terme → terme suite seq terme
    suite seq terme → op1 terme suite seq terme
    suite seq terme → ε
    terme → seq facteur
    seq facteur → facteur suite seq facteur
    suite seq facteur → op2 facteur suite seq facteur
    suite seq facteur → ε
    facteur → ENTIER
    facteur → PARO eag PARF
    op1 → PLUS
    op1 → MOINS
    op2 → MUL

*/

#endif
