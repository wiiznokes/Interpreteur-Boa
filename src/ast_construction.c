#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "ast_construction.h"

node *creer_operation(Operateur op , node *op_left , node *op_right)
{
      node *n = new_node(N_OPERATION);
      n->op = op;

      if (op_left == NULL || op_left == NULL) {
            printf("erreur: besoin de 2 operande\n") ;
	      return NULL;
      } 
      else 
      {
            n->left = op_left;
            n->right = op_right;
      }
      return n ;
}

node *creer_number(int val) { 

      node *n = new_node(N_VALUE);
      n->data_type = D_INT;
      n->number = val;

      return n;
}

node *creer_string(char *str) { 

      node *n = new_node(N_VALUE);
      n->data_type = D_CHAR;
      strcpy(n->string, str);
      
      return n;
}


node *creer_variable(char *name, DataType data_type) {

      node *n = new_node(N_VARIABLE);
      strcpy(n->name, name);
      n->data_type = data_type;
      
      return n;
}