#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include <string.h>





/*
    Helper function to recursively print a tree

    type:   0 -> racine
            1 -> left
            2 -> right
*/
static void print_tree_helper(node *n, int depth, int type)
{
    if (n == NULL)
    {
        return;
    }
    print_tree_helper(n->right, depth + 1, 1);
    for (int i = 0; i < depth; i++)
    {
        printf("│   ");
    }
    switch (type)
    {
    case 0:
        printf("├── ");
        break;
    case 1:
        printf("┌── ");
        break;
    case 2:
        printf("└── ");
        break;
    default:
        exit(1);
    }

    char log[500] = "";

    switch (n->type)
    {
    case N_VARIABLE:
    case N_CALL:
    case N_FUN:
        sprintf(log, "%s %s", data_type_to_text(n->data_type), n->name);
        break;
    case N_OPERATION:
        strcpy(log, operateur_to_text(n->op));
        break;
    case N_VALUE:
        switch (n->data_type)
        {
        case D_CHAR:
            strcpy(log, n->string);
            break;
        case D_INT:
            sprintf(log, "%d", n->number);
        default:
            break;
        }
    default:
        break;
    }
    
    printf("%s: %s\n", node_type_to_text(n->type), log);
    print_tree_helper(n->left, depth + 1, 2);
}


void print_tree(tree t)
{
    print_tree_helper(t, 0, 0);
}