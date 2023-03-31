#ifndef SYNTAX_ANALYSE_H
#define SYNTAX_ANALYSE_H

#include "stdbool.h"
#include "list.h"
#include "tree.h"

typedef enum
{
    D_INT,
    D_CHAR
} Data_type;

typedef struct
{
    Data_type type;

    char *string;
    int integer;
} variable_t;

typedef struct
{
    list args;            // list de variables
    list local_variables; // list de variables locale
} function_t;



void fill_ast(char *fileName, tree *ast);


/*
    Grammaire:

    instructions: instuction instructions
    instructions:

    instruction: initialisation ;
    instruction: assignation ;
    instruction: fonction
    instruction: if_statement
    instruction: while_loop
    instruction: for_loop


    initialisation: type name <- operation
    assignation: name = operation

    operation: name
    operation: valeur
    operation: la même que la calculette

    operations: operation operations
    operations:

    fonction: fun name ( args ) : type { instructions }

    args: operations

    if_statement: if_block else_block
    if_statement: if_block


    if_block: if ( operation ) { instructions }
    else_block: else { instructions }

    while_loop: while ( operation ) { instructions }

    for_loop: for ( operation ) { instructions }



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
