#ifndef SYNTAX_ANALYSE_H
#define SYNTAX_ANALYSE_H

#include "stdbool.h"
#include "list.h"
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
} variable;

typedef struct
{
    list args;            // list de variables
    list local_variables; // list de variables locale
} function;



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
    assignation: type name <- operation

    operation: name
    operation: valeur
    operation: la même que la calculette


    operation_or_nothing: operation
    operation_or_nothing:

    fonction: fun name ( args ) : type { instructions }

    args: operation_or_nothing

    if_statement: if_block else_block
    if_statement: if_block


    if_block: if ( operation ) { instructions }
    else_block: else { instructions }

    while_loop: while ( operation ) { instructions }

    for_loop: for ( operation ) { instructions }

*/

#endif
