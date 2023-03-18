#include <stdlib.h>
#include <stdio.h>

#include "node.h"

node *new_node()
{
    node *n = malloc(sizeof(node));
    n->left = NULL;
    n->right = NULL;

    n->val = "\0";
    return n;
}

void free_node(node *n)
{
    free(n);
}

void print_node(node *n)
{
    printf("val = %s\n", n->val);
}