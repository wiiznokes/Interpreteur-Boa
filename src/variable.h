#ifndef VARIABLE_H
#define VARIABLE_H


#include "list.h"
#include "stdbool.h"

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



bool add_global(node *n);



#endif
