#ifndef AST_CONSTRUCTION_H
#define AST_CONSTRUCTION_H



#include "node.h"
#include "tree.h"


tree *get_ast();

void free_ast();



node *creer_operation(Operateur op , node *op_left , node *op_right);



node *creer_number(int val); 


node *creer_string(char *str);


node *creer_variable(char *name, DataType data_type);

#endif