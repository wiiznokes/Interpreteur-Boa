#ifndef STACK_H
#define STACK_H


#include "node.h"
#include <stdbool.h>


void start_stack();
void free_stack();

/*
    up stack is called when we call a function
*/
bool up_stack();
void down_stack();

/*
    up scope is called when we have a new scope
    ex:
    // inside a scope
    if (1) {
        // up scope
        int a = 1;
    }
    // down scope
    
*/
bool up_scope();
void down_scope();


void add_stack(node *n);


char *get_char(char *name);
int get_int(char *name);
node *get_fun(char *name, DataType data_type);

void set_char(char *name, char *value);
void set_int(char *name, int value);



/*  
    When type == D_UNDEFINED, we only check for existence
    
    return value == D_UNDEFINED meens the variable was 
    not found (with the same name and type)
*/
DataType check_variable(
    char *name,
    DataType data_type,
    bool show_error_if_undefined);


node *get_by_name(char *name);

#endif
