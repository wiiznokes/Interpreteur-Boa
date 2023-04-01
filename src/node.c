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
    free(n);
}




char *node_type_to_text(node_type type)
{
    switch (type)
    {
    case N_INITIALISATION:
        return "N_INITIALISATION";
    case N_ASSIGNATION:
        return "N_ASSIGNATION";
    case N_VARIABLE:
        return "N_VARIABLE";
    case N_IF:
        return "N_IF";
    case N_ELSE:
        return "N_ELSE";
    case N_WHILE:
        return "N_WHILE";
    case N_FOR:
        return "N_FOR";
    case N_FUN:
        return "N_FUN";
    case N_OPERATEUR:
        return "N_OPERATEUR";
    case N_STRING:
        return "N_STRING";
    case N_NUMBER:
        return "N_NUMBER";
    }
}