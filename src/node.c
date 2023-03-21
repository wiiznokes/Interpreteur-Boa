#include <stdlib.h>
#include <stdio.h>

#include "node.h"

node *new_node(node_type type)
{
    node *n = malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;

    n->type = type;
    return n;
}

void free_node(node *n)
{
    // il faudra libered *prt en fonction de sa stucture
    free(n);
}




char *node_type_to_text(node_type type)
{
    switch (type)
    {
    case OPERATEUR:
        return "OPERATEUR";
    case VALEUR:
        return "VALEUR";
    }
}
void print_node(node *n)
{
    
    printf("%s", node_type_to_text(n->type));
}