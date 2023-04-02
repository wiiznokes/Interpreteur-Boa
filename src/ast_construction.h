#ifndef AST_CONSTRUCTION_H
#define AST_CONSTRUCTION_H



#include "node.h"

/*
    renvoie un arbre abstrait de nature OPERATEUR,  d'operateur opr 
    et ayant opde_gauche et opde_droit pour fils gauche et droit

    return NULL if error
*/
node *creer_operation(Operateur op , node *op_left , node *op_right);


/*
    renvoie un arbre abstrait "feuille", de nature OPERATION  
    et de valeur val
*/

node *creer_number(int val); 


node *creer_string(char *str);


node *creer_variable(char *name, DataType data_type);

#endif