#include <stdlib.h>
#include <stdio.h>

#include "node.h"

node *new_node()
{
    node *n = malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;

    n->type = UN_DEFINED;
    return n;
}

void free_node(node *n)
{
    // il faudra libered *prt en fonction de sa stucture
    free(n);
}

void print_node(node *n)
{
    // todo: creer un fonction qui affiche le type
    printf("val = %s\n", n->type);
}