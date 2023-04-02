#include <stdlib.h>
#include <stdio.h>

#include "node.h"


node *new_node(NodeType type)
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




char *node_type_to_text(NodeType type)
{
    switch (type)
    {
    case N_INSTRUCTION:
        return "N_INSTRUCTION";
    case N_INITIALISATION:
        return "N_INITIALISATION";
    case N_ASSIGNATION:
        return "N_ASSIGNATION";
    case N_VARIABLE:
        return "N_VARIABLE";

    case N_OPERATION:
        return "N_OPERATION";
    case N_VALUE:
        return "N_VALUE";
    case N_FUN:
        return "N_FUN";

    default:
        printf("internal error: node_type_to_text\n");
        exit(1);
    }
}