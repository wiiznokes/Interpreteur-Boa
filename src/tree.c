#include <stdlib.h>
#include <stdio.h>
#include "tree.h"



void free_tree(tree t)
{
    if (t == NULL)
    {
        return;
    }
    free_tree(t->left);
    free_tree(t->right);
    free_node(t);
}



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
    print_tree_helper(n->left, depth + 1, 1);
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
    
    printf("%s\n", node_type_to_text(n));
    print_tree_helper(n->right, depth + 1, 2);
}


void print_tree(tree t)
{
    print_tree_helper(t, 0, 0);
}