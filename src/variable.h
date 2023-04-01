#ifndef VARIABLE_H
#define VARIABLE_H

#include "stdbool.h"


#include "list.h"
#include "node.h"





/*
    - need to be a variable or a function
    - verify if a variable or a function with the same name 
    already exist inside global and local

    - add node if it's not the case, show an error msg otherwise
*/
bool add_global(node *n);


/*
    - need to be a variable
    - verify if a variable or a function with the same name 
    already exist inside global and local

    - add node if it's not the case, show an error msg otherwise
*/
bool add_local(node *n);



/*
    clear local variables
*/
void clear_local();



/*
    returns the node with the corresponding name (count <= 1 by impl)
    or returns NULL
*/
node *get_by_name(char *name);



/*  
    When type == D_UNDEFINED, we only check for existence
    
    return value == D_UNDEFINED meens the variable was 
    not found (with the same name and type)
*/
DataType check_variable(NodeType nodeType, char *name, DataType dataType);



#endif
