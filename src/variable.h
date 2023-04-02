#ifndef VARIABLE_H
#define VARIABLE_H

#include "stdbool.h"


#include "list.h"
#include "node.h"


/*
    this file is only use for the lexical analyse
*/


// init lists of variables
void start_variable();

// free list of variables
void stop_variable();



/*
    - need to be a variable or a function
    - verify if a variable or a function with the same name 
    already exist inside global and local

    - add node if it's not the case, show an error msg otherwise
*/
bool add_global_analyse(node *n);


/*
    - need to be a variable
    - verify if a variable or a function with the same name 
    already exist inside global and local

    - add node if it's not the case, show an error msg otherwise
*/
bool add_local_analyse(node *n);



/*
    clear local variables
*/
void clear_local();



/*  
    When type == D_UNDEFINED, we only check for existence
    
    return value == D_UNDEFINED meens the variable was 
    not found (with the same name and type)
*/
DataType check_variable(
    char *name,
    DataType dataType,
    bool show_error_if_undefined);



#endif
