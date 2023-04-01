#ifndef VARIABLE_H
#define VARIABLE_H

#include "stdbool.h"


#include "list.h"


typedef struct node node;


typedef enum
{
    D_UNDEFINED,
    D_UNIT, // mean nothing
    D_INT,
    D_CHAR
} data_t;



typedef struct
{
    char *name;
    data_t type;

    char *string;
    int integer;
} variable_t;

typedef struct
{
    data_t return_type;
    list args;            // list de variables
    list local_variables; // list de variables locale
} function_t;


/*
    verify if the name already exist in list.
*/
bool add_global(node *n);


/*
    the type must not be D_UNDEFINED
*/
node *new_variable(char *name, data_t type);





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
data_t check_variable(char *name, data_t type);


#endif
